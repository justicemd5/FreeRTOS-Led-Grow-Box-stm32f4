#include "filter.h"
#include "stdint.h"

/**
  * @brief Example of measure value filter
  * @param[in] measn1 Previous measure value
  * @param[in] measn  Current measure value
  * @retval Filtered measure
  */
uint16_t filter_IIR(uint16_t measn1, uint16_t measn)
{
	uint16_t val;

  val = (uint16_t)(measn << ACQ_FILTER_RANGE);

  if (measn1 != 0)
  {
    if (val > measn1)
    {
      val = measn1 + ((ACQ_FILTER_COEFF * (val - measn1)) >> 8);
    }
    else
    {
      val = measn1 - ((ACQ_FILTER_COEFF * (measn1 - val)) >> 8);
    }
  }

  return(val);
}
