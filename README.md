# mac_opengl_template

/*
 THESE FUNCTIONS WORK ====== MAKE SURE IN THE SHADER YOU PASS LIKE SO:
 
  gl_Position = position * mvp;
 
 IN THE APPLICATION, DO THE FOLLOWING:
 
 matrix4f modelview = matrix4f::translation_matrix(0.0f, 0.0f, -5.0f);
 matrix4f mvp =  modelview * perspective_matrix;
 glProgramUniformMatrix4fv(quad_program.obj(), mvp_uniform, 1, false, mvp.data());
 
 If you want to use the opengl style syntax:
 
 gl_Position = mvp * position;
 
 YOU MUST PASS TRUE FOR TRANSPOSE

 */

    template <typename T1>
    knu::math::mat4<T1> make_ortho2(T1 left, T1 right, T1 bottom, T1 top, T1 Znear, T1 Zfar)
    {
        float tx = (right + left) / (right - left);
        float ty = (top + bottom) / (top - bottom);
        float tz = (Zfar + Znear) / (Zfar - Znear);
        knu::math::mat4<T1> ortho;

        ortho = ortho.set_column_0(2 / (right - left), 0, 0, 0);
        ortho = ortho.set_column_1(0, 2 / (top - bottom), 0, 0);
        ortho = ortho.set_column_2(0, 0, 2 / (Znear - Zfar), 0);
        ortho = ortho.set_column_3(-tx, -ty, -tz, 1);

        return ortho;
    }

    template<typename T1>
    knu::math::mat4<T1> make_frustrum(T1 left, T1 right, T1 bottom, T1 top, T1 zNear, T1 zFar)
    {
        float a = 2 * zNear / (right - left);
        float b = 2 * zNear / (top - bottom);
        float A = (right + left) / (right - left);
        float B = (top + bottom) / (top - bottom);
        float C = -((zFar + zNear) / (zFar - zNear));
        float D = -((2 * zFar * zNear) / (zFar - zNear));

        knu::math::mat4<T1> frustrum;
        frustrum = frustrum.set_column_0(a, 0, 0, 0);
        frustrum = frustrum.set_column_1(0, b, 0, 0);
        frustrum = frustrum.set_column_2(A, B, C, -1);
        frustrum = frustrum.set_column_3(0, 0, D, 0);

        return frustrum;
    }
