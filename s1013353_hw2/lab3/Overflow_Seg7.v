module Overflow_Seg7(Seg7);
output [31:0] Seg7;
reg [31:0] Seg7;
initial
begin
Seg7[31:24] = 8'b10001110;
Seg7[21:16] = 8'b10001110;
Seg7[15:8] = 8'b10001110;
Seg7[7:0] = 8'b10001110;
end
endmodule