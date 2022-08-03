import common;

struct KDTree(size_t Dim) {
    // An x-split node and a y-split node are different types
    alias PD = Point!Dim;
    class Node( size_t splitDimension ){
        // If this is an x node, the next level is "y"
        // If this is a y node, the next level is "z", etc
        enum thisLevel = splitDimension;    // This lets you refer to a node's split level with theNode.thisLevel
        enum nextLevel = (splitDimension + 1) % Dim;
        Node!nextLevel left, right; // Child nodes split by the next level

        PD splitP;
        PD[] storedPs;

        this(PD[] points) { // Constructor

            if(points.length < 3) {
                storedPs = points;
                return;
            }

            auto leftPs = points.medianByDimension!thisLevel;
            auto rightPs = points[leftPs.length + 1 .. $];

            splitP = points[leftPs.length];

            left = new Node!nextLevel(leftPs);
            right = new Node!nextLevel(rightPs);
        }
    }

    // KDTree implementation

    Node!0 root;

    this(PD[] points) {
        root = new Node!0(points);
    }

    PD[] knnQuery(PD p, int k) {
        
        auto ret = makePriorityQueue!Dim(p);

        void recurse(size_t Dimension)(Node!Dimension n, AABB!Dim aabb) {
            // Check points stored
            if( isNaN(n.splitP[0])) 
            {
                foreach (point; n.storedPs) {

                    if(distance(point, p) < distance(p, ret.front)) 
                    {
                        ret.popFront;
                        ret.insert(point); 
                    }

                    else if(ret.length < k) 
                    {
                        ret.insert(point);
                    }
                }
            }

            else
            {
                if(distance(n.splitP, p) < distance(p, ret.front))
                {
                    ret.popFront;
                    ret.insert(n.splitP);

                }
                else if (ret.length < k) 
                {
                    ret.insert(n.splitP);
                }

                auto leftBB = aabb;

                leftBB.max[n.thisLevel] = n.splitP[n.thisLevel];
                if (ret.length < k || distance(p, closest(leftBB, p)) < distance(p, ret
                .front)) {
                    recurse(n.left, leftBB);
                }

                auto rightBB = aabb;
                rightBB.min[n.thisLevel] = n.splitP[n.thisLevel];
                if (ret.length < k || distance(p, closest(rightBB, p)) < distance(p, ret
                .front)) {
                    recurse(n.right, rightBB);
                }

            }
        }

        AABB!Dim rootBB;
        foreach(i; 0 .. Dim){
            rootBB.min[i] = -1 * float.infinity;
            rootBB.max[i] = float.infinity;
        }

        recurse!0(root, rootBB);

        return ret.release;
    }

    PD[] rangeQuery( PD p, float r) {

        PD[] ret;
        
        void recurse( size_t Dimension )(Node!Dimension n) {

            if (distance(n.splitP, p) < r) 
            {
                ret ~= n.splitP;
            }

            foreach(const ref point; n.storedPs) {
                if (distance(point, p) < r) 
                {
                    ret ~= point;
                }
            }

            if(n.left && p[n.thisLevel] - r < n.splitP[n.thisLevel]) 
            {
                recurse( n.left );
            }

            if(n.right && p[n.thisLevel] + r > n.splitP[n.thisLevel]) 
            {
                recurse(n.right);
            }
        }

        recurse(root);
        
        return ret;
    }

}

unittest {
    auto kdtree = KDTree!2([Point!2([.5, .5]), Point!2([1, 1]),
    Point!2([0.75, 0.4]), Point!2([0.4, 0.74])]);

    writeln(kdtree);

    writeln("kdtree rq");
    foreach(p; kdtree.rangeQuery(Point!2([1,1]), .7)){
        writeln(p);
    }
    assert(kdtree.rangeQuery(Point!2([1,1]), .7).length == 3);

    writeln("kdtree knn");
    foreach(p; kdtree.knnQuery(Point!2([1,1]), 3)){
        writeln(p);
    }
}