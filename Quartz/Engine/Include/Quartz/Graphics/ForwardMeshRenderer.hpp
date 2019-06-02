// Copyright 2019 Genten Studios
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
// following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the
// following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
// following disclaimer in the documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
// products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.

#pragma once

#include <Quartz/Graphics/RHI/IRenderDevice.hpp>
#include <Quartz/Graphics/Mesh.hpp>
#include <Quartz/Math/Matrix4x4.hpp>
#include <Quartz/Utilities/HandleAllocator.hpp>

#include <vector>

namespace qz
{
	namespace gfx
	{
		struct TextureSlotHandle : utils::HandleBase { };

		class ForwardMeshRenderer
		{
		private:
			rhi::IRenderDevice*                           m_renderDevice;
			rhi::ShaderPipelineHandle                     m_shader;
			rhi::UniformHandle                            m_viewMatrixUniform,
			                                              m_projectionMatrixUniform;

			utils::HandleAllocator<32, TextureSlotHandle> m_textureSlotsAllocator;

			struct MeshRenderData
			{
				rhi::VertexBufferHandle                   vertexBuffer;
				Mesh*                                     mesh;
				TextureSlotHandle                         textureSlot;
			};

			std::vector<MeshRenderData>                   m_meshes;

			Matrix4x4                                     m_viewMatrix,
			                                              m_projectionMatrix;

		public:
			ForwardMeshRenderer(rhi::IRenderDevice* renderDevice);

			void        create();
			void        destroy();
			void        submitMesh(Mesh* mesh);
			void        render();

			void        setProjectionMatrix(const Matrix4x4& projection);
			void        setViewMatrix(const Matrix4x4& view);

			Matrix4x4   getProjectionMatrix() const { return m_projectionMatrix; }
			Matrix4x4   getViewMatrix()        const { return m_viewMatrix; }

			std::size_t countTotalNumVertices();
		};
	}
}
