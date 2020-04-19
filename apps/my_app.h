// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"
#include "cinder/Text.h"
#include "cinder/Unicode.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace myapp {

    class MyApp : public App {
    public:

        void setup() override;

        void keyDown(KeyEvent event) override;

        void update() override;

        void draw() override;

        void PrintInstruction();

        void PrintMatrix();

        string instructions;
        Font font;
        string matrix;
        pramas buttons;
    };

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
