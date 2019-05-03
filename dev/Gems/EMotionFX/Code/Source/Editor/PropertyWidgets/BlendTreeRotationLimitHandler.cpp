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
*
*/

#include <Editor/PropertyWidgets/BlendTreeRotationLimitHandler.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <EMotionFX/Source/ConstraintTransformRotationAngles.h>
#include <AzToolsFramework/API/ToolsApplicationAPI.h>

namespace EMotionFX
{
    AZ_CLASS_ALLOCATOR_IMPL(BlendTreeRotationLimitHandler, AZ::SystemAllocator, 0);
    AZ_CLASS_ALLOCATOR_IMPL(BlendTreeRotationLimitContainerHandler, AZ::SystemAllocator, 0);
    AZ_CLASS_ALLOCATOR_IMPL(RotationLimitWdget, AZ::SystemAllocator, 0);
    AZ_CLASS_ALLOCATOR_IMPL(RotationLimitContainerWdget, AZ::SystemAllocator, 0);

    const int RotationLimitWdget::s_decimalPlaces = 1;

    RotationLimitWdget::RotationLimitWdget(QWidget* parent)
    {
        m_tooltipText = QString("Min %1 \xB0\n").arg((int)BlendTreeRotationLimitNode::RotationLimit::s_rotationLimitRangeMin);
        m_tooltipText += QString("Max %1 \xB0").arg((int)BlendTreeRotationLimitNode::RotationLimit::s_rotationLimitRangeMax);

        QHBoxLayout* hLayout = new QHBoxLayout(this);

        hLayout->setMargin(2);
        setLayout(hLayout);
        m_spinBoxMin = new MysticQt::DoubleSpinBox(this);
        layout()->addWidget(m_spinBoxMin);
        m_spinBoxMax = new MysticQt::DoubleSpinBox(this);
        layout()->addWidget(m_spinBoxMax);
        m_spinBoxMin->setRange(BlendTreeRotationLimitNode::RotationLimit::s_rotationLimitRangeMin, BlendTreeRotationLimitNode::RotationLimit::s_rotationLimitRangeMax);
        m_spinBoxMax->setRange(BlendTreeRotationLimitNode::RotationLimit::s_rotationLimitRangeMin, BlendTreeRotationLimitNode::RotationLimit::s_rotationLimitRangeMax);
        m_spinBoxMin->setDecimals(s_decimalPlaces);
        m_spinBoxMax->setDecimals(s_decimalPlaces);

        m_spinBoxMin->setToolTip(m_tooltipText);
        m_spinBoxMax->setToolTip(m_tooltipText);
        connect(m_spinBoxMin, static_cast<void (MysticQt::DoubleSpinBox::*)(double)>(&MysticQt::DoubleSpinBox::valueChanged), this, &RotationLimitWdget::HandleMinValueChanged);
        connect(m_spinBoxMax, static_cast<void (MysticQt::DoubleSpinBox::*)(double)>(&MysticQt::DoubleSpinBox::valueChanged), this, &RotationLimitWdget::HandleMaxValueChanged);
    }

    void RotationLimitWdget::SetRotationLimit(const BlendTreeRotationLimitNode::RotationLimit& rotationLimit)
    {
        m_rotationLimit = &rotationLimit;
    }

    void RotationLimitWdget::UpdateGui()
    {
        m_spinBoxMin->setValue(m_rotationLimit->GetLimitMin());
        m_spinBoxMax->setValue(m_rotationLimit->GetLimitMax());
    }

    void RotationLimitWdget::HandleMinValueChanged(double value)
    {
        m_spinBoxMin->setValue(value);
        if (m_spinBoxMin->value() <= m_spinBoxMax->value())
        {
            m_spinBoxMax->SetStyleToOk();
            m_spinBoxMin->SetStyleToOk();
            m_spinBoxMin->setToolTip(m_tooltipText);
            m_spinBoxMax->setToolTip(m_tooltipText);
            emit DataChanged();
        }
        else
        {
            m_spinBoxMin->SetStyleToError();
            QString errorTooltip = QString("The value has to be less than or equal to %1 \xB0").arg(m_spinBoxMax->value());
            m_spinBoxMin->setToolTip(errorTooltip);
        }
    }

    void RotationLimitWdget::HandleMaxValueChanged(double value)
    {
        m_spinBoxMax->setValue(value);
        if (m_spinBoxMin->value() <= m_spinBoxMax->value())
        {
            m_spinBoxMax->SetStyleToOk();
            m_spinBoxMin->SetStyleToOk();
            m_spinBoxMin->setToolTip(m_tooltipText);
            m_spinBoxMax->setToolTip(m_tooltipText);

            emit DataChanged();
        }
        else
        {
            m_spinBoxMax->SetStyleToError();
            QString errorTooltip = QString("The value has to be greater than or equal to %1 \xB0").arg(m_spinBoxMin->value());
            m_spinBoxMax->setToolTip(errorTooltip);
        }
    }


    float RotationLimitWdget::GetMin() const
    {
        return static_cast<float>(m_spinBoxMin->value());
    }

    float RotationLimitWdget::GetMax() const
    {
        return static_cast<float>(m_spinBoxMax->value());
    }

    QWidget* BlendTreeRotationLimitHandler::CreateGUI(QWidget* parent)
    {
        RotationLimitWdget* rotationLimitWdget = aznew RotationLimitWdget(parent);

        connect(rotationLimitWdget, &RotationLimitWdget::DataChanged, this, [rotationLimitWdget]()
        {
            AzToolsFramework::PropertyEditorGUIMessages::Bus::Broadcast(&AzToolsFramework::PropertyEditorGUIMessages::RequestWrite, rotationLimitWdget);
        });

        return rotationLimitWdget;
    }

    AZ::u32 BlendTreeRotationLimitHandler::GetHandlerName() const
    {
        return AZ_CRC("BlendTreeRotationLimitHandler", 0xc1af4ea8);
    }

    void BlendTreeRotationLimitHandler::ConsumeAttribute(RotationLimitWdget* /*widget*/, AZ::u32 /*attrib*/, AzToolsFramework::PropertyAttributeReader* /*attrValue*/, const char* /*debugName*/)
    {

    }

    void BlendTreeRotationLimitHandler::WriteGUIValuesIntoProperty(size_t /*index*/, RotationLimitWdget* GUI, property_t& instance, AzToolsFramework::InstanceDataNode* /*node*/)
    {
        instance.SetMin(GUI->GetMin());
        instance.SetMax(GUI->GetMax());
    }

    bool BlendTreeRotationLimitHandler::ReadValuesIntoGUI(size_t /*index*/, RotationLimitWdget* GUI, const property_t& instance, AzToolsFramework::InstanceDataNode* /*node*/)
    {
        QSignalBlocker signalBlocker(GUI);
        GUI->SetRotationLimit(instance);
        GUI->UpdateGui();
        return true;
    }



    RotationLimitContainerWdget::RotationLimitContainerWdget(QWidget* parent)
    {
        QHBoxLayout* hLayout = new QHBoxLayout(this);

        hLayout->setMargin(2);
        setLayout(hLayout);
        QLabel* headerColumn1 = new QLabel("Min angle \xB0", this);
        layout()->addWidget(headerColumn1);
        QLabel* headerColumn2 = new QLabel("Max angle \xB0", this);
        layout()->addWidget(headerColumn2);
    }


    QWidget* BlendTreeRotationLimitContainerHandler::CreateGUI(QWidget* parent)
    {
        RotationLimitContainerWdget* rotationLimitWdget = aznew RotationLimitContainerWdget(parent);

        return rotationLimitWdget;
    }

    AZ::u32 BlendTreeRotationLimitContainerHandler::GetHandlerName() const
    {
        return AZ_CRC("BlendTreeRotationLimitContainerHandler", 0xb2c775fb);
    }

    void BlendTreeRotationLimitContainerHandler::ConsumeAttribute(RotationLimitContainerWdget* /*widget*/, AZ::u32 /*attrib*/, AzToolsFramework::PropertyAttributeReader* /*attrValue*/, const char* /*debugName*/)
    { }

    void BlendTreeRotationLimitContainerHandler::WriteGUIValuesIntoProperty(size_t /*index*/, RotationLimitContainerWdget* GUI, property_t& instance, AzToolsFramework::InstanceDataNode* /*node*/)
    { }

    bool BlendTreeRotationLimitContainerHandler::ReadValuesIntoGUI(size_t /*index*/, RotationLimitContainerWdget* GUI, const property_t& instance, AzToolsFramework::InstanceDataNode* /*node*/)
    {
        return true;
    }

}