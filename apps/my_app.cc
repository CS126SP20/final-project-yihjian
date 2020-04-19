// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <NumCpp.hpp>

using namespace ci;
using namespace ci::app;

namespace myapp {

    using app::KeyEvent;

    //MyApp::MyApp() { }

    void MyApp::setup() {
        gl::enableDepthWrite();
        gl::enableDepthRead();

        gl::setMatricesWindow(getWindowSize());
        gl::enableAlphaBlending();

        //Set background to lightgrey.
        gl::clear(Color(0.83f, 0.83f, 0.83f));

        // Initialize welcome message attributes
        instructions = "Input your matrix in this format:\n"
                       "1,2,3\n"
                       "4,5,6";
        font = Font("Times New Roman", 32);

        buttons = params::InterfaceGl::create(getWindow(), "Operations", ivec2(200, 430));
        buttons->addButton("rref", bind(&MyApp::Rref, this));
        buttons->addButton("LU-Decomp", bind(&MyApp::LUDecomp, this));
        buttons->addButton("Diag", bind(&MyApp::Diag, this));
        buttons->addButton("Eigen", bind(&MyApp::Eigen, this));
        buttons->addButton("SVD", bind(&MyApp::SVD, this));
        buttons->setPosition(vec2(380,0));
        // Printout welcome message/instructions/input box
        draw();
    }

    void MyApp::update() {
        PrintMatrix();
    }

    void MyApp::draw() {
        //Rerender screen so we don't get layer over layer.
        gl::clear(Color(0.83f, 0.83f, 0.83f));
        PrintInstruction();
        buttons->draw();
        PrintMatrix();
    }

    void MyApp::keyDown(KeyEvent event) {
        if (event.getCode() == KeyEvent::KEY_BACKSPACE) {
            // Delete extra char
            if (!matrix.empty()) {
                matrix.pop_back();
            }
        } else if (event.getNativeKeyCode() == KeyEvent::KEY_RETURN) {
            // Change line
            matrix += "\n";
        } else if (event.getCharUtf32()) {
            std::u32string strUtf32(1, event.getCharUtf32());
            std::string str = ci::toUtf8(strUtf32);
            matrix += str;
        }

        draw();
    }

    void MyApp::PrintInstruction() {
        TextBox textbox = TextBox()
                .alignment(TextBox::CENTER)
                .font(font)
                .size(vec2(400,100))
                .text(instructions)
                .color(Color(0, 0, 0));

        vec2 loc = {0, 0};
        auto welcome_texture = gl::Texture::create(textbox.render());
        gl::draw(welcome_texture, loc);
    }

    void MyApp::PrintMatrix() {
        TextBox textbox = TextBox()
                .alignment(TextBox::LEFT)
                .font(font)
                .size(vec2(300,300))
                .text(matrix)
                .color(Color(0, 0, 0));

        vec2 loc = {50, 130};
        auto welcome_texture = gl::Texture::create(textbox.render());
        gl::draw(welcome_texture, loc);

        // Set color to black and draw border to our textbox
        gl::color(Color(0,0,0));
        gl::drawStrokedRect(Rectf(50,130,350,430), 5.0);
    }

    void MyApp::Rref(){};
    void MyApp::LUDecomp(){};
    void MyApp::Diag(){};
    void MyApp::Eigen(){};
    void MyApp::SVD(){};
}  // namespace myapp
