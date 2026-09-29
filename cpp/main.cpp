#include "Vpeq.h"
#include <cstdint>
#include <print>

void tick(Vpeq* circuit) {
    circuit->clk = 0;
    circuit->eval();

    circuit->clk = 1;
    circuit->eval();
}

int main(int argc, char** argv) {
    VerilatedContext context;
    context.commandArgs(argc, argv);

    Vpeq circuit{&context};

    circuit.sample_in = 0;
    circuit.rst = 1;
    tick(circuit);
    circuit.rst = 0;

    circuit.sample_in = 1000;
    tick(circuit);

    std::cout << circuit.sample_out << '\n';

    circuit.final();
}
