#include <cmath>
#include <algorithm>

#include "overmap_noise.h"
#include "simplexnoise.h"

namespace om_noise
{

float om_noise_layer_forest::noise_at( const point_om_omt &local_omt_pos ) const
{
    const point_abs_omt p = global_omt_pos( local_omt_pos );
    float r = scaled_octave_noise_3d( 4, 0.5, 0.03, 0, 1, p.x(), p.y(), get_seed() );
    r = std::pow( r, 2.0f );

    float d = scaled_octave_noise_3d( 6, 0.5, 0.07, 0, 1, p.x(), p.y(), get_seed() );
    d = std::pow( d, 3.0f );

    return std::max( 0.0f, r - d * 0.5f );
}

float om_noise_layer_floodplain::noise_at( const point_om_omt &local_omt_pos ) const
{
    const point_abs_omt p = global_omt_pos( local_omt_pos );
    float r = scaled_octave_noise_3d( 4, 0.5, 0.05, 0, 1, p.x(), p.y(), get_seed() );
    r = std::pow( r, 2.0f );
    return r;
}

float om_noise_layer_lake::noise_at( const point_om_omt &local_omt_pos ) const
{
    const point_abs_omt p = global_omt_pos( local_omt_pos );
    float r = scaled_octave_noise_3d( 8, 0.5, 0.002, 0, 1, p.x(), p.y(), get_seed() );
    r = std::pow( r, 4.0f );
    return r;
}

float om_noise_layer_ocean::noise_at( const point_om_omt &local_omt_pos ) const
{
    // this is a duplicate of lake noise.  Changing it might cause artifacts if oceans
    // and lakes intersect.
    const point_abs_omt p = global_omt_pos( local_omt_pos );
    float r = scaled_octave_noise_3d( 8, 0.5, 0.002, 0, 1, p.x(), p.y(), get_seed() );
    r = std::pow( r, 4.0f );
    return r;
}

} // namespace om_noise
