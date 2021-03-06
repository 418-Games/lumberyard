/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

#include <AzCore/Memory/Memory.h>
#include <AzCore/RTTI/RTTI.h>


namespace EMotionFX
{
    namespace Integration
    {
        class RenderActor
        {
        public:
            AZ_RTTI(EMotionFX::Integration::RenderActor, "{827A2CD5-C5FC-4D14-984D-B44A52EA92CC}")
            AZ_CLASS_ALLOCATOR_DECL

            RenderActor() = default;
            virtual ~RenderActor() = default;
        };
    } // namespace Integration
} // namespace EMotionFX
