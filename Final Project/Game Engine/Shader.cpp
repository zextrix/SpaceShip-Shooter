/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    Shader

Purpose:
Creates shader for the object

used in the application by loading and freeing surfaces

Language:   C++

Platform:
Compiler:-  Visual Studio 2017 - Visual C++ 14.1


Hardware Requirements:-		Display monitor, keyboard.

Operating System:-		Microsoft Windows 8.1+

Project:

Student Login:- pratyush.gawai
Class:- MSCS Fall2018
Assignment :- MileStone4

Author: Pratyush Gawai

Student login: pratyush.gawai

Student ID: 60001818

Creation date:  11/25/2018
---------------------------------------------------------*/

#include "Shader.h"

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>


using namespace std;

string loadFile(const char *fname) 
{
	string out,
		line;
	ifstream in(fname);
	getline(in, line);
	while (in) 
	{
		out += line + "\n";

		getline(in, line);
	}
	return out;
}


Shader::Shader()
{
	glewInit();
	if (!GLEW_VERSION_2_0) {
		std::cout << "OpenGL version 2.0 or better needed" << std::endl;
		return;
	}
}


Shader::~Shader()
{
}


int Shader::Initialize(std::string vs, std::string fs)
{
	std::string v = loadFile(vs.c_str());
	vSource = v.c_str();
	std::string f = loadFile(fs.c_str());
	fSource = f.c_str();

	// vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSource, nullptr);
	glCompileShader(vertexShader);

	// error check
	int success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "error compiling vertex shader\n" << log << std::endl;
	}

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fSource, NULL);
	glCompileShader(fragmentShader);
	//error check
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "error compiling fragment shader\n" << log << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	// check for linking errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(program, 512, NULL, log);
		std::cout << "error compiling shader\n" << log << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);// need to delete program not shader, remember for later on

	return program;
}
