#ifndef FILTER_H_
#define FILTER_H_

#include "stdint.h"

/* Noise Filter description
   ------------------------

The noise filter is a first order IRR digital filter based on the following formula:

S(n) = (1-k).S(n-1)+ k.N(n)

S(n) : sample number n of the filtered signal
N(n) : sample number n of the raw signal
k    : filter coefficient parameter in [0..1]

The filter sampling rate is the acquisition rate.

In order to optimize the implementation in the firmware, the above formula is
modified in order to have only one multiply operation:

S(n) = S(n-1) + k.(N(n) - S(n-1))

Additionally, we use k = K/256 with K an unsigned 8-bit integer.

The K is given by the ACQ_FILTER_COEFF constant.

S(n) = S(n-1) + K.(N(n) - S(n-1))/(2^8)

and the division can be done easily with bit shifting.

As we are in the digital world, this formula presents a drawback:
if the difference between S(n-1) and N(n) is less than 1/k, there will be no
difference between S(n-1) and S(n).

As a consequence, there will be a static error of up to 1/k.

In the STMTouch Driver, the S(n) is stored in the Meas element of the data
structure after each acquisition:

Meas(n) = S(n) = N(n)

The formula is then:

Meas(n) = Meas(n-1) + K.(Meas(n) - Meas(n-1))/(2^8)

In order to reduce the static error, we can use "Meas(n) = S(n).2^P".

The P is given by the ACQ_FILTER_RANGE constant.

This would shift the signal value left and provides a few additional low
significant bits useful to reduce the static error.

Warning: all thresholds must be shifted accordingly if the parameter P is
different from 0.

If we report this into the filter formula we obtain:

Meas(n) = Meas(n-1) + K.[ Meas(n)*2^P - Meas(n-1)]/2^8

In this case the static error is reduced to 1/(k.2^P)
*/

#define ACQ_FILTER_RANGE (0)   /* Range[0..5] - Warning: all thresholds must be shifted if different from 0 */

#define ACQ_FILTER_COEFF (220) /* Range[1..255] - First order filter coefficient (k = ACQ_FILTER_COEFF/256) */

uint16_t filter_IIR(uint16_t measn1, uint16_t measn);

#endif
