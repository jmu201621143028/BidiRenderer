#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <gtest/gtest.h>

#include "glyph_string.h"


class GlyphStringTest : public testing::Test {
    protected:
        void SetUp() override {
            // 每个测试样例开始之前，都会被调用。
            m_str = U"I love you. مرحبا، كيف حالك؟ I hope you are doing well. لقد كنت أفكر في مشروعنا الجديد. Let's discuss it soon!";
            const quint32* codePoints = reinterpret_cast<const quint32*>(m_str.c_str());

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
            m_glyphstr->init(codePoints, m_str.size(), face, color, parType, 
                    maxWidth);
        }

        void TearDown() override {
            // 每个测试样例结束之后，都会被调用。
            delete m_glyphstr;
            FT_Done_FreeType(m_library);
        }

        GlyphString* m_glyphstr;
        FT_Library m_library;
        std::u32string m_str;

};

std::string char32ToString(char32_t c) {
    char utf8[5] = {0};  // UTF-8 字符可能需要最多 4 字节
    if (c <= 0x7F) {
        utf8[0] = static_cast<char>(c);
    } else if (c <= 0x7FF) {
        utf8[0] = static_cast<char>((c >> 6) | 0xC0);
        utf8[1] = static_cast<char>((c & 0x3F) | 0x80);
    } else if (c <= 0xFFFF) {
        utf8[0] = static_cast<char>((c >> 12) | 0xE0);
        utf8[1] = static_cast<char>(((c >> 6) & 0x3F) | 0x80);
        utf8[2] = static_cast<char>((c & 0x3F) | 0x80);
    } else {
        utf8[0] = static_cast<char>((c >> 18) | 0xF0);
        utf8[1] = static_cast<char>(((c >> 12) & 0x3F) | 0x80);
        utf8[2] = static_cast<char>(((c >> 6) & 0x3F) | 0x80);
        utf8[3] = static_cast<char>((c & 0x3F) | 0x80);
    }
    return std::string(utf8);
}

TEST_F(GlyphStringTest, analyze) {
    EXPECT_EQ(m_glyphstr->analyze(), true);
    for (auto i = 0; i < m_str.size(); ++i) {
        LOG(INFO) << char32ToString(m_str[i]) << " runid = " << m_glyphstr->run(i);
    }
    const QVector<RunInfo>& runinfos = m_glyphstr->runInfos();
    for (auto i = 0; i < runinfos.size(); ++i) {
        RunInfo info = runinfos[i];
        LOG(INFO) << "runID = " << i 
            << ", run.startOffset = " << info.startOffset
            << ", run.endOffset = " << info.endOffset
            << ", run.direction = " << hb_direction_to_string(info.direction);
    }
}
