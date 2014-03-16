//
//  VCWindow.cpp
//  VoxelCraftOSX
//
//  Created by Alec Thilenius on 8/25/13.
//  Copyright (c) 2013 Thilenius. All rights reserved.
//

#define SHOW_GL_WARNINGS 0

#include "stdafx.h"
#include "VCGLWindow.h"
//
//#include "VCTime.h"
//
//VCWindow* VCGLWindow::ActiveWindow;
//glfwFramebuferSize resizeHandler = 0;
//
//void _glfwFramebuferSizeCallback(GLFWwindow* window, int width, int height)
//{
//	VCGLWindow::ActiveWindow->Width = width;
//	VCGLWindow::ActiveWindow->Height = height;
//	VCGLWindow::ActiveWindow->FullViewport = VCRectangle(0, 0, width, height);
//	
//	// Managed event
//	resizeHandler(width, height);
//	glViewport(0, 0, width, height);
//}
//
//
//VCWindow::VCWindow()
//{
//	VCGLWindow::ActiveWindow = this;
//}
//
//VCWindow::~VCWindow()
//{
//    
//}
//
//static void glewErrorCallback(int error, const char* description)
//{
//	VCLog::Error("GLFW Error Callback: " + std::string(description), "Initialize");
//}
//
//void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
//{
//#if SHOW_GL_WARNINGS
//	char debSource[16], debType[20], debSev[5];
//	if(source == GL_DEBUG_SOURCE_API_ARB)
//		strcpy(debSource, "OpenGL");
//	else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
//		strcpy(debSource, "Windows");
//	else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
//		strcpy(debSource, "Shader Compiler");
//	else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
//		strcpy(debSource, "Third Party");
//	else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
//		strcpy(debSource, "Application");
//	else if(source == GL_DEBUG_SOURCE_OTHER_ARB)
//		strcpy(debSource, "Other");
//
//	if(type == GL_DEBUG_TYPE_ERROR_ARB)
//		strcpy(debType, "Error");
//	else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)
//		strcpy(debType, "Deprecated behavior");
//	else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)
//		strcpy(debType, "Undefined behavior");
//	else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)
//		strcpy(debType, "Portability");
//	else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
//		strcpy(debType, "Performance");
//	else if(type == GL_DEBUG_TYPE_OTHER_ARB)
//		strcpy(debType, "Other");
//
//	if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
//	{
//		strcpy(debSev, "High");
//		SetConsoleColor(Red);
//		printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
//			debSource,debType,id,debSev,message);
//		std::cin.ignore();
//	}
//
//	else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
//	{
//		strcpy(debSev, "Medium");
//		SetConsoleColor(Red);
//		printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
//			debSource,debType,id,debSev,message);
//		std::cin.ignore();
//	}
//
//	else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
//	{
//		static std::set<std::string> postedWarnings;
//		
//		strcpy(debSev, "Low");
//		std::string post = std::string("Source:") + debSource + "\nType:" + debType + "\nID:" + std::to_string(id) + "\nSeverity:" + debSev + "\nMessage:" + message + "\n";
//
//		if(postedWarnings.find(post) == postedWarnings.end())
//		{
//			SetConsoleColor(Yellow);
//			printf("Source: %s\tType: %s\tID: %d\tSeverity: %s\nMessage: %s\n\n",
//				debSource,debType,id,debSev,message);
//
//			SetConsoleColor(White);
//			postedWarnings.insert(post);
//		}
//	}
//
//#endif
//}
//
//void VCWindow::Initalize()
//{
//	VCLog::Info("Creating a VCWindow...", "Initialize");
//    
//	// =====   GLFW   ======================================================
//	glfwSetErrorCallback(glewErrorCallback);
//
//	if (!glfwInit())
//	{
//		VCLog::Error("Creating a Failed to initialize GLFW.", "Initialize");
//		std::cin.ignore();
//	}
//	 
//	//glfwWindowHint(GLFW_DECORATED, false);
//	//glfwWindowHint(GLFW_SAMPLES, 4);
//	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//#if DEBUG
//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
//#endif
//
//	GLFWWindowHandle = glfwCreateWindow(1280, 600, "Thilenius - A 0.0.1", NULL, NULL);
//	if (!GLFWWindowHandle)
//	{
//		glfwTerminate();
//		VCLog::Error("Failed to create a window.", "Initialize");
//		std::cin.ignore();
//	}
//
//	glfwMakeContextCurrent(GLFWWindowHandle);
//
//	// =====   GLEW   ======================================================
//	glewExperimental = true;
//	GLenum glewError = glewInit();
//	if( glewError != GLEW_OK )
//	{
//		VCLog::Error("Error initializing GLEW!", "Initialize");
//		std::cin.ignore();
//	}
//
//	// =====   Debug   ======================================================
//#if DEBUG
//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
//	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
//	glDebugMessageCallbackARB(&glDebugCallback, NULL);
//#endif
//
//
//	GLint major, minor;
//	glGetIntegerv(GL_MAJOR_VERSION, &major); 
//	glGetIntegerv(GL_MINOR_VERSION, &minor);
//	VCLog::Info("OpenGL version: " + std::to_string(major) + "." + std::to_string(minor), "Initialize");
//	VCLog::Info("Hardware: " + std::string((char*)glGetString(GL_RENDERER)), "Initialize");
//	
//    
//	glfwGetWindowSize(GLFWWindowHandle, &Width, &Height);
//	FullViewport = VCRectangle(0, 0, Width, Height);
//	
//	SetVSync(false);
//	VCLog::Info("VCWindow Initialized.", "Initialize");
//    glErrorCheck();
//
//	VCInteropWindowSetPos(200, 200);
//}
//
//void VCWindow::SwapBuffers()
//{
//	VCTime::Instance->Update();
//
//	glfwSwapBuffers(GLFWWindowHandle);
//}
//
//void VCWindow::PollEvents()
//{
//	glfwPollEvents();
//}
//
//void VCWindow::SetTitle(std::string title)
//{
//	glfwSetWindowTitle(GLFWWindowHandle, title.c_str());
//}
//
//void VCWindow::SetVSync(bool enabled)
//{
//	glfwMakeContextCurrent(GLFWWindowHandle);
//
//	if (enabled)
//		glfwSwapInterval(1);
//	
//	else
//		glfwSwapInterval(0);
//}
//
//void VCInteropWindowSwapBuffers()
//{
//	VCGLWindow::ActiveWindow->SwapBuffers();
//}
//
//void VCInteropWindowPollEvents()
//{
//	VCGLWindow::ActiveWindow->PollEvents();
//}
//
//bool VCInteropWindowShouldClose()
//{
//	return glfwWindowShouldClose(VCGLWindow::ActiveWindow->GLFWWindowHandle);
//}
//
//void VCInteropWindowVSync( int enabled )
//{
//	VCGLWindow::ActiveWindow->SetVSync(enabled);
//}
//
//void VCInteropWindowGetSize(int* width, int* height)
//{
//	glfwGetWindowSize(VCGLWindow::ActiveWindow->GLFWWindowHandle, width, height);
//}
//
//void VCInteropWindowSetSize( int width, int height )
//{
//	glfwSetWindowSize(VCGLWindow::ActiveWindow->GLFWWindowHandle, width, height);
//	VCGLWindow::ActiveWindow->Height = height;
//	VCGLWindow::ActiveWindow->Width = width;
//	VCGLWindow::ActiveWindow->FullViewport = VCRectangle(0, 0, width, height);
//}
//
//void VCInteropWindowGetPos( int* x, int* y )
//{
//	glfwGetWindowPos(VCGLWindow::ActiveWindow->GLFWWindowHandle, x, y);
//}
//
//void VCInteropWindowSetPos( int x, int y )
//{
//	glfwSetWindowPos(VCGLWindow::ActiveWindow->GLFWWindowHandle, x, y);
//}
//
//void VCInteropGetMonitorSize( int* width, int* height )
//{
//	GLFWmonitor* primary = glfwGetPrimaryMonitor();
//	const GLFWvidmode* mode = glfwGetVideoMode(primary);
//	*width = mode->width;
//	*height = mode->height;
//}
//
//void VCInteropRegisterResizeCallback( glfwFramebuferSize callback )
//{
//	resizeHandler = callback;
//	glfwSetFramebufferSizeCallback(VCGLWindow::ActiveWindow->GLFWWindowHandle, _glfwFramebuferSizeCallback);
//}