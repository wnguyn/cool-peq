#include "Vpeq.h"
#include <cstdint>
#include <print>

#include "Vpeq.h"
#include <cstdint>
#include <memory>


constexpr void tick(Vpeq* circuit) {
    circuit->clk = 0;
    circuit->eval();

    circuit->clk = 1;
    circuit->eval();
}



// SUUPER DUMB BOILERPLATE!!
int main(int argc, char** argv) {
    auto ctxt = std::make_unique<VerilatedContext>();
    ctxt->commandArgs(argc, argv);
    auto dut = std::make_unique<Vpeq>(context.get());

    std::ifstream input = (
        "input.pcm",
        std::ios::binary
    );
    std::ofstream output = (
        "output.pcm",
        std::ios::binary
    );
    dut->clk = 0;
    dut->rst = 1;

    dut->sample_valid = 0;
    dut->sample_in = 0;

    for (int i = 0; i < 10; ++i) {
        tick(*dut);
    }
    int16_t input_sample;

    while (
        input.read(
            reinterpret_cast<char*>(&input_sample),
            sizeof(input_sample)
        )
    ) {
        dut->sample_in =
            static_cast<uint16_t>(input_sample);

        dut->sample_valid = 1;

        tick(*dut);

        dut->sample_valid = 0;


        while (!dut->sample_out_valid) {
            tick(*dut);
        }


        int16_t output_sample =
            static_cast<int16_t>(dut->sample_out);


        output.write(
            reinterpret_cast<const char*>(&output_sample),
            sizeof(output_sample)
        );
    }

}
