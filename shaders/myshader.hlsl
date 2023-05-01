RWTexture2D<float3> y;

[numthreads(8, 8, 1)]
void cs_5_0(uint3 i : SV_DispatchThreadID)
{
    y[i.xy] = 0.5f;
}
