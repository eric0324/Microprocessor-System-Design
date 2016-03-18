module my_pll(rst, clk_in, clk_out);

input rst, clk_in;
output reg clk_out;

parameter cnt_max = 25000000;
reg [24:0] cnt;

always@(posedge clk_in) begin
	if(rst) begin
		clk_out = 0;
		cnt = cnt_max;
	end
	
	if(cnt == 0)begin
		cnt=cnt_max;
		clk_out=!clk_out;
	end else begin
		cnt=cnt-1;
	end
end

endmodule