#include "../inc/pipeline.hpp"
#include <stdexcept>

void Pipeline::init(Context& context, Shader& shader, SDL_Window* window) {
    SDL_GPUVertexInputState vertexInputState{};
    vertexInputState.vertex_buffer_descriptions = nullptr;
    vertexInputState.num_vertex_buffers = 0;
    vertexInputState.vertex_attributes = nullptr;
    vertexInputState.num_vertex_attributes = 0;

    SDL_GPURasterizerState rasterizerState{};
    rasterizerState.fill_mode = SDL_GPU_FILLMODE_FILL;
    rasterizerState.cull_mode = SDL_GPU_CULLMODE_NONE;
    rasterizerState.front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE;

    SDL_GPUDepthStencilState depthStencilState{};
    depthStencilState.enable_depth_test = true;
    depthStencilState.enable_depth_write = false;
    depthStencilState.compare_op = SDL_GPU_COMPAREOP_LESS;

    SDL_GPUColorTargetBlendState blendState{};
    blendState.enable_blend = true;
    blendState.src_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
    blendState.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
    blendState.color_blend_op = SDL_GPU_BLENDOP_ADD;
    blendState.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
    blendState.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
    blendState.alpha_blend_op = SDL_GPU_BLENDOP_ADD;

    SDL_GPUColorTargetDescription colorTargetDescription{};
    colorTargetDescription.format = SDL_GetGPUSwapchainTextureFormat(context.device, window);
    colorTargetDescription.blend_state = blendState;

    SDL_GPUGraphicsPipelineTargetInfo targetInfo{};
    targetInfo.color_target_descriptions = &colorTargetDescription;
    targetInfo.num_color_targets = 1;
    targetInfo.has_depth_stencil_target = true;
    targetInfo.depth_stencil_format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT;

    SDL_GPUGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.vertex_shader = shader.getVertexShader();
    pipelineInfo.fragment_shader = shader.getFragmentShader();
    pipelineInfo.vertex_input_state = vertexInputState;
    pipelineInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
    pipelineInfo.rasterizer_state = rasterizerState;
    pipelineInfo.depth_stencil_state = depthStencilState;
    pipelineInfo.target_info = targetInfo;

    pipeline = SDL_CreateGPUGraphicsPipeline(context.device, &pipelineInfo);
    if (!pipeline) {
        throw std::runtime_error("Failed to create graphics pipeline");
    }
    context.particlePipeline = pipeline;
}

void Pipeline::destroy(Context& context) {
    if (pipeline) {
        SDL_ReleaseGPUGraphicsPipeline(context.device, pipeline);
        pipeline = nullptr;
        context.particlePipeline = nullptr;
    }
}

SDL_GPUGraphicsPipeline* Pipeline::getPipeline() {
    return pipeline;
}
