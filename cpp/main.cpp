#include "Vpeq.h"
#include <cstdint>
#include <print>

#include "Vpeq.h"
#include <cstdint>



constexpr void tick(Vpeq* circuit) {
    circuit->clk = 0;
    circuit->eval();

    circuit->clk = 1;
    circuit->eval();
}


// we're freaking ffing i dont want to deal with c++....
extern "C" {
    void* peq_create() {
        auto* circuit = new Vpeq;

        circuit->sample_in = 0;
        circuit->rst = 1;
        tick(circuit);
        circuit->rst = 0;

        return circuit;
    }
    // feed raw pcm from rust to get fed 
    int16_t peq_process(void* handle, int16_t sample) {
        auto* circuit = std::static_cast<Vpeq*>(handle);

        circuit->sample_in = std::static_cast<uint16_t>(sample);
        tick(circuit);

        return std::static_cast<int16_t>(circuit->sample_out);
    }

    void peq_destroy(void* handle) {
        auto* circuit = std::static_cast<Vpeq*>(handle);

        circuit->final();
        delete circuit;
    }

}
