#include "LinearAlgebra.h"


// @important Delete
Mat4 MILA::BuildModelSpaceTransform(Vec3& position, Quat& orientation, Vec3& scale)
{
    Mat4 mScale = ScaleMatrix(scale);
    Mat4 mOrien = ToMat4(orientation);
    Mat4 mTrans = TranslationMatrix(position);

    return mScale * mOrien * mTrans;
}

// @note FIX
//
Vec3 MILA::GetDirectionFromQuaternion(Quat &q)
{
    float x = (asin(q.x * 2)) * 180.0f / PI;
    float y = (asin(q.y * 2)) * 180.0f / PI;
    float z = (asin(q.z * 2)) * 180.0f / PI;

    return { x, y, z };
}

Vec3 MILA::RotateVectorByQuaternion(Vec3 &v, Quat &orientation)
{    
    // @note This method is taken from the Jorge Rodriguez videos
    // Is his optimization for the hammilton product of q * v * q' 
    // orientation * vector * Inverse(orientation)
    // But doesnt work for all the angles...
    // The Matrix multiplications are more reliable...
    //
    // Vec3 ogOriVPart = { orientation.x, orientation.y, orientation.z };
    // Quat qVec       = CreateQuaternionFromAxisAndAngle(0, v.x, v.y, v.z);
    // Vec3 vPart      = { qVec.x, qVec.y, qVec.z };
    // Vec3 vcv        = Cross(ogOriVPart, v);
    // return v + vcv * (2 * orientation.w) + Cross(vPart, vcv) * 2;    
    
    // This was my OG method, which works, but it's slower than the direct v -> q -> v
    // 
    Mat4 rotatedVector = TranslationMatrix(v) * ToMat4(orientation);
    return ExtractPositionFromMat4(rotatedVector);
}

float MILA::DegToRad(float d)
{
    return d * PI / 180.0f;
}

float MILA::RadToDeg(float r)
{
    return r * 180.0f / PI;
}
