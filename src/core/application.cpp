#include <mvcgui/core/application.h>
#include <mvcgui/internal/framework/widget_engine.h>
#include <assert.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace mvcgui {
Application::Application()
    : internal::CoreApplication{},
    close_in_next_frame_{ false }
{
}

void Application::OnInitizlize() {
}

void Application::OnProcess() {
	internal::WidgetEngine::instance().Thinking();
    if (close_in_next_frame_) {
        assert(IsDone());
    }
}

bool Application::IsDone() {
	return internal::WidgetEngine::instance().IsEmpty();
}

void Application::OnAppExit() {
}

void Application::OnDpiScaleChanged()
{
    auto& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 16 * cur_scale_.x, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->Build();
    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_CreateFontsTexture();
}

void Application::WindowWannaClose() {
    internal::WidgetEngine::instance().CloseAll();
    close_in_next_frame_ = true;
}
}