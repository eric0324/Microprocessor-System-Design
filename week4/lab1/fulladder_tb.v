module fulladder_tb();
  reg a, b, c_in;
  wire sum, c_out;
  
  fulladder fadder_inst(a,b,c_in,sum,c_out);
  
  initial begin
    a = 0;
    b = 0;
    c_in = 0;
    #80 $finish;
  end
  
  always begin
    #10 {a,b,c_in} = {a,b,c_in} + 1;
  end
endmodule