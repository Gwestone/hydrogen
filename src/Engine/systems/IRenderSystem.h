#ifndef HYDROGEN_IRENDERSYSTEM_H
#define HYDROGEN_IRENDERSYSTEM_H

namespace Engine::RenderSystems {

    class IRenderSystem{
    private:
    public:
        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
    private:
    };

} // RenderSystems

#endif //HYDROGEN_IRENDERSYSTEM_H
