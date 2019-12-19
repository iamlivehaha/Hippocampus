//
//Copyright (c) 2019 Star Platinum
//
//Created by Kong Wei Hang, 2019-12-19
//example_win32_directx11, HeavenGateEditor
//
//Add Description
//

#include "imgui.h"

#include "HeavenGateWindowColorTable.h"
#include "HeavenGateEditorUtility.h"

#include "StoryFileManager.h"
#include "StoryTable.h"
namespace HeavenGateEditor {



    HeavenGateWindowColorTable::HeavenGateWindowColorTable()
    {
        m_fileManager = new StoryFileManager;

        m_table = new StoryTable<COLOR_MAX_COLUMN>;
        m_table->SetTableType(StoryTable<COLOR_MAX_COLUMN>::TableType::Color);

        memset(m_fullPath, 0, sizeof(m_fullPath));

        HeavenGateEditorUtility::GetStoryPath(m_fullPath);
        strcat(m_fullPath, COLOR_TABLE_NAME);

        bool result = m_fileManager->LoadTableFile(m_fullPath, m_table);
        if (result == false)
        {
            m_fileManager->SaveTableFile(m_fullPath, m_table);
            m_fileManager->LoadTableFile(m_fullPath, m_table);
        }

        m_table->PushName("Color name");
        m_table->PushName("RGB Value");
    }

    HeavenGateWindowColorTable::~HeavenGateWindowColorTable()
    {

        if (m_fileManager)
        {
            delete m_fileManager;
        }
        m_fileManager = nullptr;

        if (m_table)
        {
            delete m_table;
        }
        m_table = nullptr;

    }

    void HeavenGateWindowColorTable::UpdateMainWindow()
    {
        if (m_table == nullptr)
        {
            return;
        }

        ImGui::Separator();

        ImGui::Text("Color Table");

        if (ImGui::Button("Add New Row"))
        {
            m_table->AddRow();
        }
        ImGui::SameLine();
        if (ImGui::Button("Remove Row"))
        {
            m_table->RemoveRow();
        }

        ImGui::Columns(FONT_SIZE_MAX_COLUMN + 1, "Color"); // 4-ways, with border
        ImGui::Separator();
        ImGui::Text("Index");    ImGui::NextColumn();
        for (int i = 0; i < FONT_SIZE_MAX_COLUMN; i++)
        {
            ImGui::Text(m_table->GetName(i));   ImGui::NextColumn();
        }

        //ImGui::Text("ID"); ImGui::NextColumn();
        //ImGui::Text("Name"); ImGui::NextColumn();
        //ImGui::Text("Path"); ImGui::NextColumn();
        //ImGui::Text("Hovered"); ImGui::NextColumn();
        ImGui::Separator();
        //const char* names[3] = { "One", "Two", "Three" };
        //const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
        static int selected = -1;


        char order[8] = "";
        for (int i = 0; i < m_table->GetSize(); i++)
        {
            char label[32];
            sprintf(label, "%04d", i);
            if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_None))
                selected = i;

            sprintf(order, "%d", i);
            //bool hovered = ImGui::IsItemHovered();
            ImGui::NextColumn();
            //ImGui::Text(names[i]); ImGui::NextColumn();
            //ImGui::Text(paths[i]); ImGui::NextColumn();
            //ImGui::Text("%d", hovered); ImGui::NextColumn();

            for (int j = 0; j < FONT_SIZE_MAX_COLUMN; j++)
            {
                char * content = m_table->GetContent(i, j);

                char constant[16];
                if (j % 2 == 0)
                {
                    strcpy(constant, "Alias ");

                }
                else
                {
                    strcpy(constant, "Value ");

                }
                strcat(constant, order);

                ImGui::InputText(constant, content, MAX_COLUMNS_CONTENT_LENGTH);
                ImGui::NextColumn();
            }

        }

        ImGui::Columns(1);
        ImGui::Separator();
    }

    void HeavenGateWindowColorTable::UpdateMenu()
    {
        //   ImGui::MenuItem("(dummy menu)", NULL, false, false);
        if (ImGui::MenuItem("New")) {

        }

        if (ImGui::MenuItem("Open", "Ctrl+O")) {

        }

        if (ImGui::MenuItem("Save", "Ctrl+S")) {
            m_fileManager->SaveTableFile(m_fullPath, m_table);
        }

    }

}
