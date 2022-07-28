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
            
        }
    }

}