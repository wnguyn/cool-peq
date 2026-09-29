module peq (
    input  logic               clk,
    input  logic               rst,
    input  logic signed [15:0] sample_in,
    output logic signed [15:0] sample_out
);

    always_ff @(posedge clk) begin
        if (rst)
            sample_out <= 16'sd0;
        else
            sample_out <= sample_in;
    end

endmodule
