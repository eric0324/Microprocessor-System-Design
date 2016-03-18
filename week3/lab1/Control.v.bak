module control(out_sel, addr, mem_w, sys_reset, cnt_reset, acc_clk, clk, enter, stop, reset, sw);
	
	input clk, enter, stop, reset;
	input[9:0] sw;
	
	output reg [1:0] out_sel;
	output reg [6:0] addr;
	output reg mem_w, sys_reset, cnt_reset, acc_clk;
	
	reg [1:0] state;
	
	always@(posedge clk)begin
		if(reset) begin
			state = 0;
			sys_reset = 1;
			addr=0;
			out_sel=0;
		end
		
		case(state)
			0: begin
				cnt_reset = 1;
				
				if(enter)
					state=1;
				end
				
			1: begin
				sys_reset = 0;
				acc_clk = enter;
				
				if(enter)
					mem_w=1;
				else
					begin
					if(mem_w)
						begin
							addr=addr+1;
							cnt_reset=1;
							mem_w=0;
						end
					else
						cnt_reset=0;
					end
					
					if(stop)
						state=2;
				end
			2: begin
				cnt_reset=1;
				mem_w=0;
				addr=sw;
				
				if(addr==0)
					out_sel=1;
				else
					out_sel=2;
				end	
		endcase
	end
endmodule