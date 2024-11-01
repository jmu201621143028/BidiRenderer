#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <gtest/gtest.h>

#include "glyph_string.h"


class GlyphStringTest : public testing::Test {
    protected:
        void SetUp() override {
            // 每个测试样例开始之前，都会被调用。
            std::u32string str(U"مرحبا، كيف حالك؟ I hope you are doing well. لقد كنت أفكر في مشروعنا الجديد. Let's discuss it soon!");
            const quint32* codePoints = reinterpret_cast<const quint32*>(str.c_str());

            // FreeType 初始化
            if (FT_Init_FreeType(&m_library)) {
                FAIL() << "FT_Init_FreeType error";
            }

            // 加载字体
            FT_Face face;
            FriBidiParType parType = FRIBIDI_PAR_ON;
            const char* fontfile = "../../fonts/DejaVuSans.ttf";
            if (FT_Error error = FT_New_Face(m_library, fontfile, 0, &face)) {
                FAIL() << "FT_New_Face error: " << error;
            }

            // 设置字体大小
            if (int error = FT_Set_Pixel_Sizes(face, 0, 48)) {
                FAIL() << "FT_Set_Pixel_Sizes error: " << error;
            }

            QColor color(100, 149, 237);
            int maxWidth = 500;
            m_glyphstr = new GlyphString();
            m_glyphstr->init(codePoints, str.size(), face, color, parType, 
                    maxWidth);
        }

        void TearDown() override {
            // 每个测试样例结束之后，都会被调用。
            delete m_glyphstr;
            FT_Done_FreeType(m_library);
        }

        GlyphString* m_glyphstr;
        FT_Library m_library;
};

TEST_F(GlyphStringTest, analyze) {
    m_glyphstr->analyze();
}