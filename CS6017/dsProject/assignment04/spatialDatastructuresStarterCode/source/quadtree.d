import common;

struct QuadTree(size_t Dim) {
    alias P2 = Point!2;
    alias AABB2 = AABB!2;
    struct Node {

        // Variables
        P2[] points; // List of points if it's a leaf node
        Node[4] children; // 4 children if it's an internal node
        AABB2 aabb; // AABB that explains what area this node covers
        bool isLeaf; // Is node a leaf node or not
        P2 midpoint; // Midpoint of the Node or the area it covers.

        // Constants
        int MAX_POINTS = 2;

        this(P2[] points, AABB2 aabb) {
            if(points.length <= MAX_POINTS)
            {
                this.points = points.dup;
                this.isLeaf = true;
            } 
            else
            {
                midpoint = (aabb.max + aabb.min) / 2; // Calculate the midpoint of the area.

                // Calculate points in each horizontal half.
                auto rightPoints = points.partitionByDimension!0(midpoint[0]);
                auto leftPoints = points[0..$ - rightPoints.length];

                // Calculate points in each quarter.
                auto topRightPoints = rightPoints.partitionByDimension!1(midpoint[1]);
                auto topLeftPoints = leftPoints.partitionByDimension!1(midpoint[1]);
                auto bottomRightPoints = rightPoints[0 .. $ - topRightPoints.length];
                auto bottomLeftPoints = leftPoints[0 .. $ - topLeftPoints.length];

                // Calculate bounding boxes of each quarter
                auto topLeftBB = boundingBox!Dim([Point!Dim([aabb.min[0], midpoint[1]]), Point!Dim([midpoint[0], aabb.max[1]])]);
                auto topRightBB = boundingBox!Dim([midpoint, aabb.max]);
                auto bottomLeftBB = boundingBox!Dim([aabb.min, midpoint]);
                auto bottomRightBB = boundingBox!Dim([Point!Dim([midpoint[0], aabb.min[1]]), Point!Dim([aabb.max[0], midpoint[1]])]);

                // Add childrens
                children ~= Node(topLeftPoints, topLeftBB);
                children ~= Node(topRightPoints, topRightBB);
                children ~= Node(bottomLeftPoints, bottomLeftBB);
                children ~= Node(bottomRightPoints, bottomRightBB);
            }
        }

        P2[] rangeQuery(P2 p, float r) {
            P2[] recurse(Node n) {
                if(n.isLeaf) {
                    P2[] ret;
                    foreach( const ref point; n.points) {
                        if(distance(p, point) < r) {
                            ret ~= point;
                        }
                    }
                    return ret;
                }
                else
                {
                    int[] indices;

                    auto x_difference = p[0] - n.midpoint[0];
                    auto y_difference = p[1] - n.midpoint[1];

                    if(x_difference < 0) 
                    {
                        if(y_difference < 0)
                        {
                            indices ~= 2;

                            if (r > x_difference)
                            {
                                indices ~= 3;
                            }

                            if (r > y_difference)
                            {
                                indices ~= 0;
                            }
                            if (r > x_difference && r > y_difference)
                            {
                                indices~= 1;
                            }

                        }
                        else
                        {
                            indices ~= 0;

                            if (r > x_difference) {
                                indices ~= 1;
                            }
                            if (r > y_difference) {
                                indices ~= 2;
                            }
                            if (r > y_difference && r > x_difference) {
                                indices ~= 3; 
                            }

                        }
                    }
                    else
                    {
                        if (y_difference < 0) {
                            indices ~= 3;

                            if (r > x_difference) 
                            {
                                indices ~= 2;
                            }
                            if (r > y_difference) 
                            {
                                indices ~= 1;
                            }
                            if (r > y_difference && r > x_difference) 
                            {
                                indices ~= 0; 
                            }
                        } 
                        else {
                            indices ~= 1;

                            if (r > x_difference) {
                                indices ~= 0;
                            }
                            if (r > y_difference) {
                                indices ~= 3;
                            }
                            if (r > y_difference && r > x_difference) {
                                indices ~= 2; 
                            }
                        }
                    }

                    P2[] ret;
                    
                    foreach(const ref i; indices) {
                        ret ~= n.children[i].rangeQuery(p, r);
                    }
                    return ret;
                }
            }
            return recurse(this);
        }

        P2[] knnQuery(P2 p, int k) {
            auto ret = makePriorityQueue!2(p);

            void recurse(Node n) {
                if(n.isLeaf) {
                    foreach(const ref point; n.points) {
                        if(ret.length < k) {
                            ret.insert(point);
                        }
                        else if (distance(point, p) < distance(p, ret.front)) {
                            ret.popFront;
                            ret.insert(point);
                        }
                    }
                }
                else
                {
                    foreach(const ref child; n.children) {
                        if(distance(p, closest(child.aabb, p)) < distance(p, ret.front) || ret.length < k)
                        {
                            recurse(child);
                        }
                    }
                }
            }
            recurse(this);
            ret = ret.release;
            return ret;
        }
    }

    Node root;

    this(P2[] points, AABB2 aabb) {
        this.root = Node(points, aabb);
    }

    P2[] rangeQuery(P2 p, float r) {
        return root.rangeQuery(p, r);
    }

    P2[] knnQuery(P2 p, int k) {
        return root.knnQuery(p, k);
    }
}