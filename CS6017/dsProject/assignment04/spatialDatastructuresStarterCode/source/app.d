import std.stdio;

import common;
import dumbknn;
import bucketknn;
import kdtree;
import quadtree;

void main()
{

    writeln("struct,time,k,N,dim. I have it done this way so that it is easier to make a csv manually.");


    static foreach(dim; 1..8){{
        foreach(N; [100, 1000, 10000, 100000]) {

            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto kd = DumbKNN!dim(trainingPoints);

            auto sw = StopWatch(AutoStart.no);

            foreach(k; [2,4,8,16,32,64]) {
                sw.start;

                foreach(const ref qp; testingPoints){
                    kd.knnQuery(qp, k);
                }

                sw.stop;

                writeln("dumbKNN,", sw.peek.total!"usecs", ",", k, ",", N, ",", dim);
            }

        }
    }}



    static foreach(dim; 1..8){{
        foreach(N; [100, 1000, 10000, 100000]) {

            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto kd = BucketKNN!dim(trainingPoints, cast(int) pow(N/64, 1.0/dim));

            auto sw = StopWatch(AutoStart.no);

            foreach(k; [2,4,8,16,32,64]) {
                sw.start;

                foreach(const ref qp; testingPoints){
                    kd.knnQuery(qp, k);
                }

                sw.stop;

                writeln("bucketKNN,", sw.peek.total!"usecs", ",", k, ",", N, ",", dim);
            }
        }
    }}


    static foreach(dim; 2..3){{
        foreach(N; [100, 1000, 10000, 100000]) {

            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto quad = QuadTree!dim(trainingPoints, boundingBox(trainingPoints));

            auto sw = StopWatch(AutoStart.no);

            foreach(k; [2,4,8,16,32,64]) {
                sw.start;

                foreach(const ref qp; testingPoints){
                    quad.knnQuery(qp, k);
                }

                sw.stop;

                writeln("quadTree,", sw.peek.total!"usecs", ",", k, ",", N, ",", dim);
            }
        }
    }}


    static foreach(dim; 1..8){{
        foreach(N; [100, 1000, 10000, 100000]) {

            auto trainingPoints = getUniformPoints!dim(N);
            auto testingPoints = getUniformPoints!dim(100);

            auto kd = KDTree!dim(trainingPoints);

            auto sw = StopWatch(AutoStart.no);

            foreach(k; [2,4,8,16,32,64]){

                sw.start;

                foreach(const ref qp; testingPoints){
                    kd.knnQuery(qp, k);
                }

                sw.stop;

                writeln("kdTree,", sw.peek.total!"usecs", ",", k, ",", N, ",", dim);
            }
        }
    }}
}
