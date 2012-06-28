/*-----------------------------------------------------------------------------

 1999, Steinberg Soft und Hardware GmbH, All Rights Reserved

-----------------------------------------------------------------------------*/

#include "Bitcrusher.hpp"
//#include "BitcrusherEdit.cpp"
//#include "BCEditor.cpp"
//#include "c_radio_group.cpp"

//-------------------------------------------------------------------------------------------------------

DistrhoPluginBase* createDistrhoPlugin()
{
    return new Bitcrusher((void*)1); // make audioMaster ptr non-null
}
