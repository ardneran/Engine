//
//  GlModel.h
//  Application
//
//  Created by Narendra Umate on 3/16/14.
//
//

#ifndef __Application__GlModel__
#define __Application__GlModel__

#include <string>
#include "GlProgram.h"
#include "GlShader.h"
#include "../../../Mathematics/Matrix.h"
#include "../../../External/stbi/StbImage.h"
#include "../../../External/tinyobjloader/tiny_obj_loader.h"

namespace Engine
{
	class GlModel
	{
	public:
		GlModel(const GLuint& programId, const Mat4* viewMatrixPtr, const std::string& objFilePath, const std::string& mtlBasePath);
		~GlModel();

		void draw();

		void updateViewMatrix();

		void pushPerspectiveMatrix(const Mat4* perspectiveMatrix);
		void pushOrthographicMatrix(const Mat4* orthographicMatrix);

		void setPosition(const Vec3& position);
		void setRotation(const Vec3& rotation);
		void setScale(const Vec3& scale);

	private:
		void updateModelMatrix();
		void updateModelViewMatrix();
		void updateNormMatrix();

		void pushModelMatrix();
		void pushViewMatrix();
		void pushModelViewMatrix();
		void pushNormMatrix();

		//void pushTextureSamplers();

		GLuint m_programId;

		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		Mat4 m_modelMatrix;
		const Mat4* m_viewMatrixPtr;
		Mat4 m_modelViewMatrix;
		Mat3 m_normMatrix;
//----------------------------------------------------------------------------//
		enum Vao { VaoTriangles, VaoCount };
		enum Vbo { VboPosition, VboNormal, VboTexCoord, VboIndex, VboCount };
		enum Attribute { AttributePosition, AttributeNormal, AttributeTexCoord, AttributeCount };
		enum Texture { TextureDiffuse, TextureCount };
		enum TextureSampler { TextureSamplerDiffuse, TextureSamplerCount };

		GLuint m_vaos[VaoCount];
		GLuint m_vbos[VboCount];
		GLuint m_textures[TextureCount];
		GLuint m_textureSamplers[TextureCount];
		GLuint m_indexCount;
//----------------------------------------------------------------------------//
	};
}
#endif /* defined(__Application__GlModel__) */
