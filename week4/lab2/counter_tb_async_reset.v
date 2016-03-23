module counter_tb_async_reset();
  reg clk, rst, en;
  wire [9:0] counter_out;
  
  counter counter_inst(clk, rst, en,counter_out);
  
  initial begin
    clk = 0;
    rst = 1;
    en = 1;
    #2 rst = 0;
    #32 rst = 1;
    #52 rst = 0;
  end
  
  always begin
    #5 clk = !clk;
  end
endmodule