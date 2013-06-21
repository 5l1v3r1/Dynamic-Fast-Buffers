#ifndef _CPP_EXCEPTIONS_WRONGTYPEEXCEPTION_H_
#define _CPP_EXCEPTIONS_WRONGTYPEEXCEPTION_H_

#include "FastCdr.h"
#include "FastBuffer.h"

namespace DynamicFastBuffers
{
	/*!
	* @brief This class is thrown as an exception when a parameter with a wrong type_ attribute has been specified.
    * @ingroup EXCEPTIONMODULE
	*/
	class eProsima_cpp_DllVariable WrongTypeException : public eProsima::Exception
	{
	public:

		/*!
		* @brief Default constructor.
		*
		* @param message An error message. This message is copied.
		*/
		WrongTypeException (const std::string &message);
		
		/*!
		* @brief Default constructor.
		*
		* @param message An error message. This message is moved.
		*/
		WrongTypeException (std::string&& message);
		
		/*!
		* @brief Default copy constructor.
		*
		* @param ex WrongTypeException that will be copied.
		*/
		WrongTypeException (const WrongTypeException  &ex);
		
		/*!
		* @brief Default move constructor.
		*
		* @param ex WrongTypeException that will be moved.
		*/
		WrongTypeException (WrongTypeException && ex);
		
		/*!
		* @brief Assigment operation.
		*
		* @param ex WrongTypeException that will be copied.
		*/
		WrongTypeException & operator=(const WrongTypeException  &ex);
		
		/*!
		* @brief Assigment operation.
		*
		* @param ex WrongTypeException that will be moved.
		*/
		WrongTypeException & operator=(WrongTypeException && ex);
		
		//! @brief Default constructor
		virtual ~WrongTypeException () EPROSIMA_USE_NOEXCEPT;
		
		//! @brief This function throws the object as exception.
		virtual void raise() const;
	};
}

#endif //_CPP_EXCEPTIONS_WRONGTYPEEXCEPTION_H_