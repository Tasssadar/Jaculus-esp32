#pragma once

#include <jac/machine/machine.h>
#include <jac/machine/functionFactory.h>
#include <jac/machine/class.h>

#include <noal_func.h>
#include <memory>
#include <unordered_map>
#include <SmartLeds.h>

#include <set>


template<>
struct jac::ConvTraits<Rgb> {
    static Value to(ContextRef ctx, Rgb val) {
        auto obj = Object::create(ctx);
        obj.set<int>("r", val.r);
        obj.set<int>("g", val.g);
        obj.set<int>("b", val.b);
        return obj;
    }

    static Rgb from(ContextRef ctx, ValueWeak val) {
        auto obj = val.to<Object>();
        return Rgb(obj.get<int>("r"), obj.get<int>("g"), obj.get<int>("b"));
    }
};


template<class Next>
class NeopixelFeature : public Next {
    static inline std::set<int> _usedRmtChannels;

    struct NeopixelProtoBuilder : public jac::ProtoBuilder::Opaque<SmartLed>, public jac::ProtoBuilder::Properties {
        static SmartLed* constructOpaque(JSContext* ctx, std::vector<jac::ValueWeak> args) {
            if (args.size() != 2) {
                throw std::runtime_error("Invalid number of arguments");
            }
            int pin = args[0].to<int>();
            int count = args[1].to<int>();

            if (Next::PlatformInfo::PinConfig::DIGITAL_PINS.find(pin) == Next::PlatformInfo::PinConfig::DIGITAL_PINS.end()) {
                throw std::runtime_error("Invalid pin number");
            }

            int channel = 0;
            while (_usedRmtChannels.find(channel) != _usedRmtChannels.end()) {
                channel++;
            }
            if (channel >= 4) {
                throw std::runtime_error("No available RMT channels");
            }
            _usedRmtChannels.insert(channel);

            return new SmartLed(LED_WS2812, count, pin, channel, SingleBuffer);
        }

        static void destroyOpaque(JSRuntime* rt, SmartLed* ptr) noexcept {
            if (!ptr) {
                return;
            }

            ptr->wait();
            int channel = ptr->getChannel();
            delete ptr;
            _usedRmtChannels.erase(channel);
        }

        static void addProperties(JSContext* ctx, jac::Object proto) {
            jac::FunctionFactory ff(ctx);

            proto.defineProperty("show", ff.newFunctionThis([](jac::ContextRef ctx, jac::ValueWeak thisValue) {
                SmartLed& led = *getOpaque(ctx, thisValue);
                led.wait();
                led.show();
            }), jac::PropFlags::Enumerable);

            proto.defineProperty("set", ff.newFunctionThis([](jac::ContextRef ctx, jac::ValueWeak thisValue, int idx, Rgb color) {
                SmartLed& strip = *getOpaque(ctx, thisValue);
                strip[idx] = color;
            }), jac::PropFlags::Enumerable);

            proto.defineProperty("get", ff.newFunctionThis([](jac::ContextRef ctx, jac::ValueWeak thisValue, int idx) {
                SmartLed& strip = *getOpaque(ctx, thisValue);
                return strip[idx];
            }), jac::PropFlags::Enumerable);
        }
    };
public:
    using NeopixelClass = jac::Class<NeopixelProtoBuilder>;

    NeopixelFeature() {
        NeopixelClass::init("Neopixel");
    }

    void initialize() {
        Next::initialize();

        auto& mod = this->newModule("neopixel");
        jac::Function ctor = NeopixelClass::getConstructor(this->context());
        mod.addExport("Neopixel", ctor);
    }
};
