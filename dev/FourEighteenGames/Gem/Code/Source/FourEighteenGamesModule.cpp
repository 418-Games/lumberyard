
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include <FourEighteenGamesSystemComponent.h>

namespace FourEighteenGames
{
    class FourEighteenGamesModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(FourEighteenGamesModule, "{CB33CCBA-3C57-4389-99FF-09EE731AAFFD}", AZ::Module);
        AZ_CLASS_ALLOCATOR(FourEighteenGamesModule, AZ::SystemAllocator, 0);

        FourEighteenGamesModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                FourEighteenGamesSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<FourEighteenGamesSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(FourEighteenGames_b8fae83078d2495fbab1df261a991587, FourEighteenGames::FourEighteenGamesModule)
