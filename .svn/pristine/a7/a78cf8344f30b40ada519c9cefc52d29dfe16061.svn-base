#include "Transform.h"

//========================================//
//		       Initialization			  //
//========================================//

void fTransform::Initialize(Transform &transform)
{
	transform.position	  = { 0.0f, 0.0f, 0.0f		 };
	transform.orientation = { 0.0f, 0.0f, 0.0f, 1.0f };
	transform.scale		  = { 1.0f, 1.0f, 1.0f		 };
	transform.model		  = Identity();
}

Transform fTransform::Initialize()
{
	Transform transform;
	transform.position         = { 0.0f, 0.0f, 0.0f		  };
	transform.orientation      = { 0.0f, 0.0f, 0.0f, 1.0f };	
	transform.scale		       = { 1.0f, 1.0f, 1.0f		  };
	transform.model			   = Identity();

	return transform;
}

Transform fTransform::Initialize(Vec3 position, Quat orientation, Vec3 scale)
{
	Transform transform;
	transform.position	  = position;
	transform.orientation = orientation;
	transform.scale		  = scale;

	Mat4 t = TranslationMatrix(position);
	Mat4 r = ToMat4(orientation);
	Mat4 s = ScaleMatrix(scale);

	transform.model = s * r * t;

	return transform;
}

Transform fTransform::Initialize(Vec3 position, Vec3 eulerAngles, Vec3 scale)
{
	Transform transform;
	transform.position    = position;
	transform.orientation = EulerToQuaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	transform.scale       = scale;

	Mat4 t = TranslationMatrix(position);
	Mat4 r = ToMat4(transform.orientation);
	Mat4 s = ScaleMatrix(scale);

	transform.model = s * r * t;

	return transform;
}

//========================================//
//		      Reference Update			  //
//========================================//

void fTransform::UpdatePosition(Transform &t, Vec3 p)
{
	if (t.position != p)
	{
		t.position = p;		
		t.model	   = ModelMatrixRST(t.position, t.orientation, t.scale);
	}
}

void fTransform::UpdateOrientation(Transform &t, Quat q)
{		
	if (q != t.orientation)
	{
		t.orientation = q;				
		t.model		  = ModelMatrixRST(t.position, t.orientation, t.scale);
	}
}

void fTransform::UpdateOrientation(Transform &t, Vec3 o)
{
	Quat q = EulerToQuaternion(o.x, o.y, o.z);

	if (t.orientation != q)
	{
		t.orientation = q;
		t.model		  = ModelMatrixRST(t.position, t.orientation, t.scale);
	}
}

void fTransform::UpdateScale(Transform &t, Vec3 s)
{
	if (t.scale != s)
	{
		t.scale = s;		
		t.model = ModelMatrixRST(t.position, t.orientation, t.scale);		
	}
}


//========================================//
//		       Pointer Update  	          //
//========================================//

void fTransform::UpdatePosition(Transform *t, Vec3 p)
{
	if (t != nullptr)
	{
		if (t->position != p)
		{
			t->position = p;
			t->model    = ModelMatrixRST(t->position, t->orientation, t->scale);
		}
	}
}

void fTransform::UpdateOrientation(Transform *t, Quat q)
{
	if (t != nullptr)
	{							
		if (q != t->orientation)
		{				
			t->orientation = q;								
			t->model	   = ModelMatrixRST(t->position, t->orientation, t->scale);
		}
	}
} 

void fTransform::UpdateScale(Transform *t, Vec3 s)
{
	if (t != nullptr)
	{
		if (t->scale != s)
		{						
			t->scale = s;
			t->model = ModelMatrixRST(t->position, t->orientation, t->scale);			
		}
	}
}

//========================================//
//		Whole Transform Update World	  //
//========================================//

void fTransform::Update(Transform &transform, Vec3 position, Vec3 orientation, Vec3 scale)
{	
	Quat qorientation = EulerToQuaternion(orientation.x, orientation.y, orientation.z);
	if (transform.position == position && transform.orientation == qorientation && transform.scale == scale) { return; }

	transform.position	  = position;	
	transform.orientation = qorientation;
	transform.scale		  = scale;
	transform.model		  = ModelMatrixRST(transform.position, transform.orientation, transform.scale);
}

void fTransform::Update(Transform &transform, Vec3 position, Quat orientation, Vec3 scale)
{
	if (transform.position == position && transform.orientation == orientation && transform.scale == scale) { return; }

	transform.position	  = position;
	transform.orientation = orientation;
	transform.scale		  = scale;	
	transform.model		  = ModelMatrixRST(transform.position, transform.orientation, transform.scale);
}

void fTransform::Update(Transform *transform, Vec3 position, Quat orientation, Vec3 scale)
{
	transform->position    = position;
	transform->orientation = orientation;
	transform->scale       = scale;
	transform->model	   = ModelMatrixRST(transform->position, transform->orientation, transform->scale);
}

void fTransform::UpdateModelMatrix(Transform &transform)
{
	transform.model = ModelMatrixRST(transform.position, transform.orientation, transform.scale);
}