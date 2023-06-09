#pragma once
#include <assert.h>
#include <charconv>
#include <functional>
#include <string_view>

// json stream
//
// TODO:
// use std::to_chars if clang implements
//
namespace gltfjson {

using StringSink = std::function<void(std::string_view)>;

enum StackFlags
{
  STACKFLAG_None = 0,
  STACKFLAG_Root = 0x01,
  STACKFLAG_Array = 0x02,
  STACKFLAG_Object = 0x04,
  STACKFLAG_Comma = 0x08,
  STACKFLAG_Collon = 0x10,
};

class JsonWriter
{
  StringSink m_writer;
  char m_buf[1024];
  StackFlags m_stack[124] = { STACKFLAG_Root };
  int m_depth = 1;

public:
  JsonWriter(const StringSink& sink)
    : m_writer(sink)
  {
  }

  ~JsonWriter() { assert(m_depth == 1); }

  JsonWriter(const JsonWriter&) = delete;
  JsonWriter& operator=(const JsonWriter&) = delete;

  void push(std::string_view str)
  {
    if (m_stack[m_depth - 1] & STACKFLAG_Comma) {
      assert((m_stack[m_depth - 1] & STACKFLAG_Root) == 0);
      if (m_stack[m_depth - 1] & STACKFLAG_Collon) {
        m_writer(":");
        m_stack[m_depth - 1] =
          static_cast<StackFlags>(m_stack[m_depth - 1] & ~STACKFLAG_Collon);
      } else {
        m_writer(",");
      }
    } else {
      m_stack[m_depth - 1] =
        static_cast<StackFlags>(m_stack[m_depth - 1] | STACKFLAG_Comma);
    }
    m_writer(str);
  }

  void array_open()
  {
    push("[");
    m_stack[m_depth++] = STACKFLAG_Array;
  }

  void array_close()
  {
    assert(m_depth > 0);
    assert(m_stack[m_depth - 1] & STACKFLAG_Array);
    --m_depth;
    m_writer("]");
  }

  void object_open()
  {
    push("{");
    m_stack[m_depth++] = STACKFLAG_Object;
  }

  void object_close()
  {
    assert(m_depth > 0);
    assert(m_stack[m_depth - 1] & STACKFLAG_Object);
    --m_depth;
    m_writer("}");
  }

  void null() { push("null"); }

  void value(bool is_true)
  {
    if (is_true) {
      push("true");
    } else {
      push("false");
    }
  }

  void value(int value)
  {
    auto len = snprintf(m_buf, sizeof(m_buf), "%d", value);
    push({ m_buf, m_buf + len });
  }

  void value(uint32_t value)
  {
    auto len = snprintf(m_buf, sizeof(m_buf), "%u", value);
    push({ m_buf, m_buf + len });
  }

  void value(size_t value)
  {
    auto len = snprintf(m_buf, sizeof(m_buf), "%zu", value);
    push({ m_buf, m_buf + len });
  }

  void value(float value)
  {
#if 0
    auto len = snprintf(m_buf, sizeof(m_buf), "%f", value);
    push({ m_buf, m_buf + len });
#else
    auto begin = std::begin(m_buf);
    auto end = std::end(m_buf);
    if (auto [ptr, ec] = std::to_chars(begin, end, value); ec == std::errc{}) {
      // std::cout << std::string_view(begin, ptr - begin) << std::endl;
      push(std::string_view(begin, ptr - begin));
    }
#endif
  }

  void value(std::string_view str)
  {
    // TODO: quote
    push("\"");
    m_writer(str);
    m_writer("\"");
  }
  void value(std::u8string_view str)
  {
    value(std::string_view((const char*)str.data(), str.size()));
  }

  void value(const char* str) { value(std::string_view(str)); }

  void key(std::string_view str)
  {
    value(str);
    m_stack[m_depth - 1] =
      static_cast<StackFlags>(m_stack[m_depth - 1] | STACKFLAG_Collon);
  }
  void key(std::u8string_view str)
  {
    key(std::string_view((const char*)str.data(), str.size()));
  }
};

}
