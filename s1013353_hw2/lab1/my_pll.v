module my_pll(clk_in, clk_out);
input clk_in;
output clk_out;
reg clk_out;
parameter counter_max = 1000000;
reg [19:0] counter_1;

initial
begin
	clk_out = 1'b0;
	counter_1 = counter_max;
end

always@(posedge clk_in)
begin
	if(counter_1 == 0)
	begin
		counter_1 = counter_max;
		clk_out = !clk_out;
	end
	else
		counter_1 = counter_1 - 1;
end
endmodule