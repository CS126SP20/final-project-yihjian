// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <NumCpp.hpp>
#include <mylibrary/matrixsolver.h>

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
        matrix = "";

        buttons = params::InterfaceGl::create(getWindow(), "Operations", ivec2(200, 430));
        buttons->addButton("Det", bind(&MyApp::Det, this));
        buttons->addButton("Eigen(in development)", bind(&MyApp::Eigen, this));
        buttons->addButton("Inverse", bind(&MyApp::Inv, this));
        buttons->addButton("LU-Decomp", bind(&MyApp::LUDecomp, this));
        buttons->addButton("rref", bind(&MyApp::Rref, this));
        buttons->addButton("SVD", bind(&MyApp::SVD, this));

        gl::color(1,1,1);
        buttons->addSeparator();
        buttons->addText("Input params as");
        buttons->addText("\"1.0, 2, 3.33\"");
        buttons->addSeparator();
        buttons->addText("Power Iterations");
        buttons->addParam("Inital Guess", &initial_guess);
        buttons->addButton("Do 1 Iteration", bind(&MyApp::PowerIteration, this));
        buttons->addSeparator();

        buttons->addText("Least Square");
        buttons->addParam("b", &b);
        buttons->addButton("solve", bind(&MyApp::LstSq, this));
        buttons->addSeparator();

        buttons->setPosition(vec2(380, 0));
        // Printout welcome message/instructions/input box
        draw();
    }

    void MyApp::update() {
        draw();
    }

    void MyApp::draw() {
        //Rerender screen so we don't get layer over layer.
        gl::clear(Color(0.83f, 0.83f, 0.83f));
        PrintInstruction();
        buttons->draw();
        PrintMatrix();
        PrintResult();
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
                .size(vec2(400, 100))
                .text(instructions)
                .color(Color(0, 0, 0));

        vec2 loc = {0, 0};
        auto welcome_texture = gl::Texture::create(textbox.render());
        gl::draw(welcome_texture, loc);
    }

    void MyApp::PrintMatrix() {
        TextBox textbox = TextBox()
                .alignment(TextBox::LEFT)
                .font(Font("Times New Roman", 24))
                .size(vec2(300, 300))
                .text(matrix)
                .color(Color(0, 0, 0));

        vec2 loc = {50, 130};
        auto input_matrix = gl::Texture::create(textbox.render());
        gl::draw(input_matrix, loc);

        // Set color to black and draw border to our textbox
        gl::color(Color(0, 0, 0));
        gl::drawStrokedRect(Rectf(50, 130, 350, 430), 5.0);
    }

    void MyApp::PrintResult() {
        TextBox textbox = TextBox()
                .alignment(TextBox::LEFT)
                .font(Font("Times New Roman", 24))
                .size(vec2(500, 500))
                .text("Result:\n" + solved_mat)
                .color(Color(0, 0, 0));

        vec2 loc = {50, 460};
        auto result_matrices = gl::Texture::create(textbox.render());
        gl::draw(result_matrices, loc);

        gl::color(Color(0, 0, 0));
        gl::drawStrokedRect(Rectf(50, 460, 550, 960), 5.0);
    }

    // Following are button handlers
    void MyApp::Rref() {
        solved_mat = matrixsolver::Rref(matrix);
    }

    void MyApp::LUDecomp() {
        solved_mat = matrixsolver::LUDecomp(matrix);
    }

    void MyApp::Det() {
        solved_mat = matrixsolver::Det(matrix);
    }

    void MyApp::Inv() {
        solved_mat = matrixsolver::Inv(matrix);
    }

    void MyApp::SVD() {
        solved_mat = matrixsolver::SVD(matrix);
    }

    void MyApp::Eigen() {
        solved_mat = matrixsolver::Eigen(matrix);
    }

    void MyApp::PowerIteration() {
        solved_mat = matrixsolver::PowerIter(matrix, initial_guess);
    }

    void MyApp::LstSq() {
        solved_mat = "lstsq";
    }
}  // namespace myapp
