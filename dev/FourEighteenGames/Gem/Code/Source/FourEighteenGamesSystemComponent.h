
#pragma once

#include <AzCore/Component/Component.h>

#include <FourEighteenGames/FourEighteenGamesBus.h>

namespace FourEighteenGames
{
    class FourEighteenGamesSystemComponent
        : public AZ::Component
        , protected FourEighteenGamesRequestBus::Handler
    {
    public:
        AZ_COMPONENT(FourEighteenGamesSystemComponent, "{2A6BD3F8-8AB9-4FB6-9FD2-07B070C8FCD1}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // FourEighteenGamesRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };

} // namespace FourEighteenGames
