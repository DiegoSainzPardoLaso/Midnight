// ============================================================================================================================================================
// @note Matrix multiplication occurs from left to right. So for example the MVP matrix would be, M*V*P, instead of the opengl version of P*V*M
// @note Projection and View matrices returns are transposed, because OpenGL is Column major, so it goes from top to bottom instead of from left to right
//
//
// ============================================================================================================================================================
#pragma once

#include <cstdio>
#include <cmath>
#include "Vector.h"
#include "Quaternion.h"
#include "MathConstants.h"

#include "../Engine/EngineConfig.h"


struct Mat4
{	
	float data[16];

	Mat4 operator * (Mat4 o) 
	{
		return
		{
			data[0]  * o.data[0] + data[1]  * o.data[4] + data[2]  * o.data[8]  + data[3]  * o.data[12],
			data[0]  * o.data[1] + data[1]  * o.data[5] + data[2]  * o.data[9]  + data[3]  * o.data[13],
			data[0]  * o.data[2] + data[1]  * o.data[6] + data[2]  * o.data[10] + data[3]  * o.data[14],
			data[0]  * o.data[3] + data[1]  * o.data[7] + data[2]  * o.data[11] + data[3]  * o.data[15],
					 					    					   						   
			data[4]  * o.data[0] + data[5]  * o.data[4] + data[6]  * o.data[8]  + data[7]  * o.data[12],
			data[4]  * o.data[1] + data[5]  * o.data[5] + data[6]  * o.data[9]  + data[7]  * o.data[13],
			data[4]  * o.data[2] + data[5]  * o.data[6] + data[6]  * o.data[10] + data[7]  * o.data[14],
			data[4]  * o.data[3] + data[5]  * o.data[7] + data[6]  * o.data[11] + data[7]  * o.data[15],
					 					    
			data[8]  * o.data[0] + data[9]  * o.data[4] + data[10] * o.data[8]  + data[11] * o.data[12],
			data[8]  * o.data[1] + data[9]  * o.data[5] + data[10] * o.data[9]  + data[11] * o.data[13],
			data[8]  * o.data[2] + data[9]  * o.data[6] + data[10] * o.data[10] + data[11] * o.data[14],
			data[8]  * o.data[3] + data[9]  * o.data[7] + data[10] * o.data[11] + data[11] * o.data[15],

			data[12] * o.data[0] + data[13] * o.data[4] + data[14] * o.data[8]  + data[15] * o.data[12],
			data[12] * o.data[1] + data[13] * o.data[5] + data[14] * o.data[9]  + data[15] * o.data[13],
			data[12] * o.data[2] + data[13] * o.data[6] + data[14] * o.data[10] + data[15] * o.data[14],
			data[12] * o.data[3] + data[13] * o.data[7] + data[14] * o.data[11] + data[15] * o.data[15],
		};
	};
 
	void operator *= (const Mat4 &o)
	{
		data[0]  = data[0]  * o.data[0] + data[1]  * o.data[4] + data[2]  * o.data[8]  + data[3]  * o.data[12];
		data[1]  = data[0]  * o.data[1] + data[1]  * o.data[5] + data[2]  * o.data[9]  + data[3]  * o.data[13];
		data[2]  = data[0]  * o.data[2] + data[1]  * o.data[6] + data[2]  * o.data[10] + data[3]  * o.data[14];
		data[3]  = data[0]  * o.data[3] + data[1]  * o.data[7] + data[2]  * o.data[11] + data[3]  * o.data[15];
				 		    					   						  						  
		data[4]  = data[4]  * o.data[0] + data[5]  * o.data[4] + data[6]  * o.data[8]  + data[7]  * o.data[12];
		data[5]  = data[4]  * o.data[1] + data[5]  * o.data[5] + data[6]  * o.data[9]  + data[7]  * o.data[13];
		data[6]  = data[4]  * o.data[2] + data[5]  * o.data[6] + data[6]  * o.data[10] + data[7]  * o.data[14];
		data[7]  = data[4]  * o.data[3] + data[5]  * o.data[7] + data[6]  * o.data[11] + data[7]  * o.data[15];
						    					   
		data[8]  = data[8]  * o.data[0] + data[9]  * o.data[4] + data[10] * o.data[8]  + data[11] * o.data[12];
		data[9]  = data[8]  * o.data[1] + data[9]  * o.data[5] + data[10] * o.data[9]  + data[11] * o.data[13];
		data[10] = data[8]  * o.data[2] + data[9]  * o.data[6] + data[10] * o.data[10] + data[11] * o.data[14];
		data[11] = data[8]  * o.data[3] + data[9]  * o.data[7] + data[10] * o.data[11] + data[11] * o.data[15];

		data[12] = data[12] * o.data[0] + data[13] * o.data[4] + data[14] * o.data[8]  + data[15] * o.data[12];
		data[13] = data[12] * o.data[1] + data[13] * o.data[5] + data[14] * o.data[9]  + data[15] * o.data[13];
		data[14] = data[12] * o.data[2] + data[13] * o.data[6] + data[14] * o.data[10] + data[15] * o.data[14];
		data[15] = data[12] * o.data[3] + data[13] * o.data[7] + data[14] * o.data[11] + data[15] * o.data[15];
	};
	
	Vec4 operator * (const Vec4 &o)
	{
		return
		{
			o.x * data[0]  + o.y * data[1]  + o.z * data[2]  + o.w * data[3],
			o.x * data[4]  + o.y * data[5]  + o.z * data[6]  + o.w * data[7],
			o.x * data[8]  + o.y * data[9]  + o.z * data[10] + o.w * data[11],
			o.x * data[12] + o.y * data[13] + o.z * data[14] + o.w * data[15],
		};
	}

	Mat4 operator * (float f)
	{
		return 
		{
			data[0]  * f, data[1]  * f, data[2]  * f, data[3]  * f,
			data[4]  * f, data[5]  * f, data[6]  * f, data[7]  * f,
			data[8]  * f, data[9]  * f, data[10] * f, data[11] * f,
			data[12] * f, data[13] * f, data[14] * f, data[15] * f,
		};
	}

	Mat4 operator / (float f)
	{
		return 
		{
			data[0]  / f, data[1]  / f, data[2]  / f, data[3]  / f,
			data[4]  / f, data[5]  / f, data[6]  / f, data[7]  / f,
			data[8]  / f, data[9]  / f, data[10] / f, data[11] / f,
			data[12] / f, data[13] / f, data[14] / f, data[15] / f,
		};
	}
	
	float operator () (int x, int y) 
	{
		if (x > 3) { x = 3; }
		if (y > 3) { y = 3; }
		if (x < 0) { x = 0; }
		if (y < 0) { y = 0; }

		return data[x + y * 4]; 
	}
	
	float operator [] (int x) { return data[x]; }	 	
};

Mat4  Identity();
Mat4  Transpose(Mat4 &m);
Mat4  Inverse(Mat4 &m);
Mat4  Adjoint(Mat4 &m);
float Determinant(Mat4 &m);

Mat4 ModelMatrixRST(Vec3 &position, Quat &orientation, Vec3 &scale);
Mat4 ModelMatrixSRT(Vec3 &position, Quat &orientation, Vec3 &scale); 

Mat4 TranslationMatrix(Vec3 &newPosition);

Mat4 ScaleMatrix(Vec3 &newScale);
Mat4 ScaleFromPoint(float scale, Vec3 &point);
Mat4 ScaleFromPoint(Vec3 &scale, Vec3 &point);

Mat4 ToMat4 (Quat &q);
Mat4 RotateAroundAPoint(Quat q, Vec3 p);
Mat4 RotateX(float f);
Mat4 RotateY(float f);
Mat4 RotateZ(float f);
Mat4 RotationMatrix(Vec3 rotation, float angle);

Mat4 PerspectiveProjectionMatrix(int width, int height, float fov, float zNear, float zFar);
Mat4 OrthographicMatrix(float left, float right, float top, float bottom, float zNear, float zFar);
Mat4 ViewMatrix(Vec3 &position, Vec3 &lookAtPosition, Vec3 &worldUp);

Vec3 ExtractPositionFromMat4(Mat4 &m);
Vec3 ExtractScaleFromMatrix (Mat4 &modelMatrix, Quat &orientation);
void Print(const char* name, Mat4& m);