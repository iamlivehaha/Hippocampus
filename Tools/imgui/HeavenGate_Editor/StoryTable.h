//
//  StoryTable.hpp
//  example_osx_opengl2
//
//  Created by 威化饼干 on 7/12/2019.
//  Copyright © 2019 ImGui. All rights reserved.
//

#ifndef StoryTable_h
#define StoryTable_h

#include <stdio.h>
#include <vector>

#include "nlohmann/json.hpp"
#include "HeavenGateEditorConstant.h"


namespace HeavenGateEditor {
    using json = nlohmann::json;
    using std::vector;

    template<int column>
    class StoryRow
    {
    public:
        StoryRow();
        ~StoryRow();

        int Size()const;
        bool IsFull()const;
        bool Push(const char* content);
        bool Set(int index, const char * content);
        const char* Get(int index)const;
    private:
        int m_size;
        char(*m_content)[MAX_COLUMNS_CONTENT_LENGTH];
    };

    template<int column>
    class StoryTable {
        enum TableType
        {
            Font_Size,
            Font_Color
        };

    public:
        StoryTable();
        ~StoryTable();

        bool PushName(const char* name);
        bool SetName(int index, const char * name);
        bool PushContent(const char * content);
        bool SetContent(int rowIndex, int index, const char* content);
        const char* GetName(int index);
        const char* GetContent(int rowIndex, int index);

    private:
        int m_rowSize;
        StoryRow<column>* m_name;
        vector<StoryRow<column>*> m_content;


    };

    template<int column>
    void to_json(json& j, const StoryTable< column>& p);

    template<int column>
    void to_json(json& j, const StoryRow<column>& p);

    template< int column>
    void from_json(const json& j, StoryTable< column>& p);

    template<int row>
    void from_json(const json& j, StoryRow<row>& p);


}

#endif /* StoryTable_h */
