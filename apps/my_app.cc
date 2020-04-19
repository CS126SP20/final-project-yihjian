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

        // Printout welcome message/instructions
        PrintInstruction();

        PrintMatrix();
    }

    void MyApp::update() {
        PrintMatrix();
    }

    void MyApp::draw() {
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

        PrintMatrix();
    }

    void MyApp::PrintInstruction() {

        TextBox textbox = TextBox()
                .alignment(TextBox::CENTER)
                .font(font)
                .size(vec2(500,100))
                .text(instructions)
                .color(Color(0, 0, 0));

        vec2 loc = {0, 0};
        auto welcome_texture = gl::Texture::create(textbox.render());
        gl::draw(welcome_texture, loc);
    }

    void MyApp::PrintMatrix() {
        //Rerender screen so we don't get layer over layer.
        gl::clear(Color(0.83f, 0.83f, 0.83f));
        PrintInstruction();

        TextBox textbox = TextBox()
                .alignment(TextBox::LEFT)
                .font(font)
                .size(vec2(300,300))
                .text(matrix)
                .color(Color(0, 0, 0));

        vec2 loc = {100, 130};
        auto welcome_texture = gl::Texture::create(textbox.render());
        gl::draw(welcome_texture, loc);

        // Set color to black and draw border to our textbox
        gl::color(Color(0,0,0));
        gl::drawStrokedRect(Rectf(100,130,400,430), 5.0);
    }
}  // namespace myapp
