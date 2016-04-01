#pragma once

namespace Raptor {

	class Variable;

	struct TypeInfo {

		void *(*_new)(size_t);
		void  (*_del)(void *);

	};

	class Variable {

		public:

			enum {

				INT = 0,
				UINT,
				CHAR,
				UCHAR,
				BOOL,
				LONG,
				ULONG,
				LONGLONG,
				ULONGLONG,
				FLOAT,
				DOUBLE,
				STRING,
				FUNCTION,
				EXTERN

			};

			Variable();
			Variable(const Variable &v);

			Variable(int i);
			Variable(unsigned int i);
			Variable(char c);
			Variable(unsigned char c);
			Variable(bool b);
			Variable(long l);
			Variable(unsigned long l);
			Variable(long long l);
			Variable(unsigned long long l);
			Variable(float f);
			Variable(double d);
			Variable(const char *s);
			Variable(const Str &s);

			inline operator int() const;
			inline operator unsigned int() const;
			inline operator char() const;
			inline operator unsigned char() const;
			inline operator bool() const;
			inline operator long() const;
			inline operator unsigned long() const;
			inline operator long long() const;
			inline operator unsigned long long() const;
			inline operator float() const;
			inline operator double() const;
			inline operator const char *() const;
			inline operator Str() const;

			inline operator void *() const;

			template <class T>
			inline operator T &() const;
			template <class T>
			inline operator T *() const;
			template <class T>
			inline operator const T &() const;
			template <class T>
			inline operator const T *() const;

		private:

			TypeInfo type_info;
			mutable void *data = NULL;

		private:

			Ptr<unsigned int> use_count { new unsigned int(1) };

	};

}