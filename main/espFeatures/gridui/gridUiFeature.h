#pragma once

#include <memory>
#include <esp_log.h>
#include <map>

#include <jac/machine/machine.h>
#include <jac/machine/functionFactory.h>
#include <noal_func.h>

#include <gridui.h>

#include "widgets/_common.h"

class GridUiHolder {
    TaskHandle_t _webServerTask;
    std::unique_ptr<rb::Protocol> _protocol;

public:
    GridUiHolder() : _webServerTask(nullptr) { }

    void begin(jac::ContextRef context, std::string ownerName, std::string deviceName, jac::Function builderCallback);
    void end(jac::ContextRef context);
};

template<class Next>
class GridUiFeature : public Next {
    GridUiHolder _holder;

public:
    GridUiFeature() {
    }

    void initialize() {
        Next::initialize();

        using namespace gridui;
        using namespace std::placeholders;

        gridui_jac::GridUiContext::get().setScheduleEvent([this](std::function<void()> event) {
            this->scheduleEvent(event);
        });

        jac::FunctionFactory ff(this->context());

        jac::Module& griduiModule = this->newModule("gridui");

        griduiModule.addExport("begin", ff.newFunction(noal::function([this](std::string ownerName, std::string deviceName, jac::Function builderCallback){
            _holder.begin(this->context(), ownerName, deviceName, builderCallback);
        })));
        griduiModule.addExport("end", ff.newFunction(noal::function([this]() {
            _holder.end(this->context());
        })));

        griduiModule.addExport("version", ff.newFunction(noal::function([](){
            return RB_GRIDUI_VERSION;
        })));
    }

    ~GridUiFeature() {
        _holder.end(this->context());
        gridui_jac::GridUiContext::get().setScheduleEvent(nullptr);
    }
};
