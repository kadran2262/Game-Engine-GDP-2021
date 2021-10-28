#ifndef _GLCommon_HG_
#define _GLCommon_HG_
#include <string>
// The order I included these can cause 
// build error if they are backwards.

// include glm
#define GLM_ENABLE_EXPERIMENTAL  // for euler_angles.hpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/euler_angles.hpp>

// personal glm "extensions"
#include <glm/james/mat4stack.h>
#include <glm/james/inline_helpers.h>
#include <glm/james/aabb.h>
#include <glm/james/rotation_from_to.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#endif 