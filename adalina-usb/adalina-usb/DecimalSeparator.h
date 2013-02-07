//
//  DecimalSeparator.h
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 07/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__DecimalSeparator__
#define __adalina_usb__DecimalSeparator__

#include <iostream>
template<typename CharT>
class DecimalSeparator : public std::numpunct<CharT>
{
public:
    DecimalSeparator(CharT Separator)
    : m_Separator(Separator)
    {}
    
protected:
    CharT do_decimal_point()const
    {
        return m_Separator;
    }
    
private:
    CharT m_Separator;
};
#endif /* defined(__adalina_usb__DecimalSeparator__) */
