#pragma once

#include <jac/machine/functionFactory.h>
#include <gridui.h>
#include "./_common.h"

namespace gridui_jac {

class SliderWidget {
    static JSValue setColor(JSContext* ctx_, JSValueConst thisVal, JSValueConst val) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        widget.setColor(jac::ValueWeak(ctx_, val).to<std::string>());
        return JS_UNDEFINED;
    }
    static JSValue color(JSContext* ctx_, JSValueConst thisVal) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        return jac::Value::from(ctx_, widget.color()).loot().second;
    }

    static JSValue setFontSize(JSContext* ctx_, JSValueConst thisVal, JSValueConst val) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        widget.setFontSize(jac::ValueWeak(ctx_, val).to<float>());
        return JS_UNDEFINED;
    }
    static JSValue fontSize(JSContext* ctx_, JSValueConst thisVal) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        return jac::Value::from(ctx_, widget.fontSize()).loot().second;
    }

    static JSValue setMin(JSContext* ctx_, JSValueConst thisVal, JSValueConst val) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        widget.setMin(jac::ValueWeak(ctx_, val).to<float>());
        return JS_UNDEFINED;
    }
    static JSValue min(JSContext* ctx_, JSValueConst thisVal) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        return jac::Value::from(ctx_, widget.min()).loot().second;
    }

    static JSValue setMax(JSContext* ctx_, JSValueConst thisVal, JSValueConst val) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        widget.setMax(jac::ValueWeak(ctx_, val).to<float>());
        return JS_UNDEFINED;
    }
    static JSValue max(JSContext* ctx_, JSValueConst thisVal) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        return jac::Value::from(ctx_, widget.max()).loot().second;
    }

    static JSValue setValue(JSContext* ctx_, JSValueConst thisVal, JSValueConst val) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        widget.setValue(jac::ValueWeak(ctx_, val).to<float>());
        return JS_UNDEFINED;
    }
    static JSValue value(JSContext* ctx_, JSValueConst thisVal) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        return jac::Value::from(ctx_, widget.value()).loot().second;
    }

    static JSValue setPrecision(JSContext* ctx_, JSValueConst thisVal, JSValueConst val) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        widget.setPrecision(jac::ValueWeak(ctx_, val).to<float>());
        return JS_UNDEFINED;
    }
    static JSValue precision(JSContext* ctx_, JSValueConst thisVal) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        return jac::Value::from(ctx_, widget.precision()).loot().second;
    }

    static JSValue setShowValue(JSContext* ctx_, JSValueConst thisVal, JSValueConst val) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        widget.setShowValue(jac::ValueWeak(ctx_, val).to<bool>());
        return JS_UNDEFINED;
    }
    static JSValue showValue(JSContext* ctx_, JSValueConst thisVal) {
        auto& widget = widgetOpaque<gridui::Slider>(thisVal);
        return jac::Value::from(ctx_, widget.showValue()).loot().second;
    }

public:
    static void getProperty(const char *name, qjsGetter* getter, qjsSetter *setter) {
        if(strcmp(name, "color") == 0) {
            *getter = color;
            *setter = setColor;
            return;
        }
        if(strcmp(name, "fontSize") == 0) {
            *getter = fontSize;
            *setter = setFontSize;
            return;
        }
        if(strcmp(name, "min") == 0) {
            *getter = min;
            *setter = setMin;
            return;
        }
        if(strcmp(name, "max") == 0) {
            *getter = max;
            *setter = setMax;
            return;
        }
        if(strcmp(name, "value") == 0) {
            *getter = value;
            *setter = setValue;
            return;
        }
        if(strcmp(name, "precision") == 0) {
            *getter = precision;
            *setter = setPrecision;
            return;
        }
        if(strcmp(name, "showValue") == 0) {
            *getter = showValue;
            *setter = setShowValue;
            return;
        }
    }
};

};
