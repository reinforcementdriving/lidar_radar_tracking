#include "inc/global.h"
#include "inc/objectsimulator.h"
#include "inc/visualizer.h"
#include "inc/tracker.h"

int main()
{
    ObjectSimulator sim;
    Visualizer viser;
    Tracker radar_tracker;

    uint64_t frame_cnt = 0;  
    std::vector<BoxObject> gt;
    std::vector<RadarObject> radarobjs;
    std::vector<BoxObject> filtered_radarobjs;
    while (frame_cnt++ < 60 / update_period)
    {
        sim.GenerateGT(gt);
        sim.GenerateRadarObsv(gt, radarobjs);

        radar_tracker.ekf(radarobjs, filtered_radarobjs);

        viser.Init();
        viser.DrawGT(gt, cv::Scalar(0,255,0));
        viser.DrawRadarObjs(radarobjs, cv::Scalar(0,0,255));
        viser.DrawGT(filtered_radarobjs, cv::Scalar(255,255,0));

        viser.ShowMap();
        usleep(50000);
    }

    return 0;
}
