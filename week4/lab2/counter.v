module counter(clk, rst,en,out);
  
  input clk, rst,en;
  output reg [9:0] out;
  
  always@(posedge clk or posedge rst) begin
    if(rst) begin
      out = 0;
    end else begin
      if (en) begin
        out = out + 1;
      end
      if(out == 30) out = out +1;
    end
  end
endmodule