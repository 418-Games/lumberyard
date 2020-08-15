
#include <FourEighteenGamesSystemComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

namespace FourEighteenGames
{
    void FourEighteenGamesSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<FourEighteenGamesSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<FourEighteenGamesSystemComponent>("FourEighteenGames", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void FourEighteenGamesSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("FourEighteenGamesService"));
    }

    void FourEighteenGamesSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("FourEighteenGamesService"));
    }

    void FourEighteenGamesSystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        AZ_UNUSED(required);
    }

    void FourEighteenGamesSystemComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        AZ_UNUSED(dependent);
    }

    void FourEighteenGamesSystemComponent::Init()
    {
    }

    void FourEighteenGamesSystemComponent::Activate()
    {
        FourEighteenGamesRequestBus::Handler::BusConnect();
    }

    void FourEighteenGamesSystemComponent::Deactivate()
    {
        FourEighteenGamesRequestBus::Handler::BusDisconnect();
    }

} // namespace FourEighteenGames
