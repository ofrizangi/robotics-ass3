#include <Krembot/controller/krembot_controller.h>
#include <queue>

using namespace std;


struct MapMsg{
    int ** occupancyGrid;
    int ** weightedGrid;
    Real resolution;
    CVector2 origin;
    int height, width;
};

struct PosMsg{
    CVector2 pos;
    CDegrees degreeX;
};


class WSTC_controller : public KrembotController {
private:
    Real robotSize = 0.20;
    bool isFirst = true;
public:
    MapMsg mapMsg;
    PosMsg posMsg;

    ParticleObserver Particle;
    ~WSTC_controller() = default;
    void setup();
    void loop();
    void pos_to_col_row(CVector2 pos, int * pCol, int * pRow);
    void save_grid_to_file(string name, int** grid, int _height, int _width);
    void save_grid_to_file_with_robot_location(string name, int** grid, int _height,
                                                                     int _width, int robot_col, int robot_row);

    void Init(TConfigurationNode &t_node) override {
        KrembotController::Init(t_node);
        if ( ! krembot.isInitialized() ) {
            throw std::runtime_error("krembot.ino.cpp: krembot wasn't initialized in controller");
        }
        Particle.setName(krembot.getName());
    }
    void ControlStep() override {
        if(isFirst) {
            setup();
            isFirst = false;
        }
        loop();
    }
};


REGISTER_CONTROLLER(WSTC_controller, "WSTC_controller")
