/*
 	A Calculator application from basic java UI tools.
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.script.ScriptEngineManager; //for managing mathematical calculations
import javax.script.ScriptEngine; //for managing mathematical calculations

//primary Calculator class
public class Calculator extends JFrame implements ActionListener
{
	String expr="",evl="";
	JLabel disp,dec_label,bin_label,oct_label,hex_label;
	JTextField tf,dec,bin,oct,hex;
	TextArea ta;ScrollPane pane;
	ScriptEngineManager mgr = new ScriptEngineManager();
    ScriptEngine engine = mgr.getEngineByName("JavaScript");
    
    //function to set the UI for different calculator types depending on the passed flag
	void setFrame(int choice)
	{
		getContentPane().removeAll();
		if(choice == 0)
		{
			setSize(1000, 800);
			Button b[],b_add,b_sub,b_div,b_mul,b_eql,b_dot,b_com,b_pi,
			b_brko,b_brkc,b_sin,b_cos,b_tan,b_log,b_pow,b_sqrt,b_mod,b_del;
			disp = new JLabel("= Answer");
			disp.setBounds(530, 50, 400, 50);
			disp.setForeground(new Color(28, 64, 99));
			disp.setFont(new Font("answer_font", Font.BOLD, disp.getHeight()));
			add(disp);
			
			tf=new JTextField();
			tf.setBounds(50, 50, 440, 50);
			tf.setBackground(new Color(204, 204, 166));
			tf.setText("Expression");
			tf.setFont(new Font("expression_font", Font.PLAIN, tf.getHeight()-15));
			tf.setEditable(false);
			add(tf);
			
			ta=new TextArea();
			ta.setText("History\n-----------------------------------------------------------");
			ta.setEditable(false);
			ta.setBackground(new Color(164, 152, 77));
			ta.setBounds(530, 120, 400, 580);
			ta.setFont(new Font("history_font", Font.BOLD, 20));
			pane=new ScrollPane();
			pane.add(ta);
			add(ta);
			
			int k=0,j=120;
			b = new Button[10];
			for(int i=0;i<10;i++)
			{
				b[i]=new Button(Integer.toString(i));
				b[i].setBackground(Color.black);
				b[i].setForeground(Color.white);
				b[i].setFont(new Font("button_font", Font.PLAIN, b[i].getHeight()+25));
				b[i].setBounds(50+(k*90), j, 80, 80);
				b[i].addActionListener(this);
				add(b[i]);
				if(i==4)
				{
					j+=100;k=0;
				}
				else
				{
					k++;
				}
			}
			
			j+=100;k=0;
			b_add=new Button("+");
			b_add.setBackground(Color.black);
			b_add.setForeground(Color.white);
			b_add.setFont(new Font("button_font", Font.PLAIN, b_add.getHeight()+25));
			b_add.setBounds(50+(k*90), j, 80, 80);
			b_add.addActionListener(this);
			add(b_add);k++;
			b_sub=new Button("-");
			b_sub.setBackground(Color.black);
			b_sub.setForeground(Color.white);
			b_sub.setFont(new Font("button_font", Font.PLAIN, b_sub.getHeight()+25));
			b_sub.setBounds(50+(k*90), j, 80, 80);
			b_sub.addActionListener(this);
			add(b_sub);k++;
			b_div=new Button("/");
			b_div.setBackground(Color.black);
			b_div.setForeground(Color.white);
			b_div.setFont(new Font("button_font", Font.PLAIN, b_div.getHeight()+25));
			b_div.setBounds(50+(k*90), j, 80, 80);
			b_div.addActionListener(this);
			add(b_div);k++;
			b_mul=new Button("x");
			b_mul.setBackground(Color.black);
			b_mul.setForeground(Color.white);
			b_mul.setFont(new Font("button_font", Font.PLAIN, b_mul.getHeight()+25));
			b_mul.setBounds(50+(k*90), j, 80, 80);
			b_mul.addActionListener(this);
			add(b_mul);k++;
			b_dot=new Button(".");
			b_dot.setBackground(Color.black);
			b_dot.setForeground(Color.white);
			b_dot.setFont(new Font("button_font", Font.PLAIN, b_dot.getHeight()+25));
			b_dot.setBounds(50+(k*90), j, 80, 80);
			b_dot.addActionListener(this);
			add(b_dot);j+=100;k=0;
			b_brko=new Button("(");
			b_brko.setBackground(Color.black);
			b_brko.setForeground(Color.white);
			b_brko.setFont(new Font("button_font", Font.PLAIN, b_brko.getHeight()+25));
			b_brko.setBounds(50+(k*90), j, 80, 80);
			b_brko.addActionListener(this);
			add(b_brko);k++;
			b_brkc=new Button(")");
			b_brkc.setBackground(Color.black);
			b_brkc.setForeground(Color.white);
			b_brkc.setFont(new Font("button_font", Font.PLAIN, b_brkc.getHeight()+25));
			b_brkc.setBounds(50+(k*90), j, 80, 80);
			b_brkc.addActionListener(this);
			add(b_brkc);k++;
			b_pow=new Button("pow");
			b_pow.setBackground(Color.black);
			b_pow.setForeground(Color.white);
			b_pow.setFont(new Font("button_font", Font.PLAIN, b_pow.getHeight()+15));
			b_pow.setBounds(50+(k*90), j, 80, 80);
			b_pow.addActionListener(this);
			add(b_pow);k++;
			b_sqrt=new Button("sqrt");
			b_sqrt.setBackground(Color.black);
			b_sqrt.setForeground(Color.white);
			b_sqrt.setFont(new Font("button_font", Font.PLAIN, b_sqrt.getHeight()+15));
			b_sqrt.setBounds(50+(k*90), j, 80, 80);
			b_sqrt.addActionListener(this);
			add(b_sqrt);k++;
			b_mod=new Button("%");
			b_mod.setBackground(Color.black);
			b_mod.setForeground(Color.white);
			b_mod.setFont(new Font("button_font", Font.PLAIN, b_mod.getHeight()+15));
			b_mod.setBounds(50+(k*90), j, 80, 80);
			b_mod.addActionListener(this);
			add(b_mod);j+=100;k=0;
			b_sin=new Button("sin");
			b_sin.setBackground(Color.black);
			b_sin.setForeground(Color.white);
			b_sin.setFont(new Font("button_font", Font.PLAIN, b_sin.getHeight()+15));
			b_sin.setBounds(50+(k*90), j, 80, 80);
			b_sin.addActionListener(this);
			add(b_sin);k++;
			b_cos=new Button("cos");
			b_cos.setBackground(Color.black);
			b_cos.setForeground(Color.white);
			b_cos.setFont(new Font("button_font", Font.PLAIN, b_cos.getHeight()+15));
			b_cos.setBounds(50+(k*90), j, 80, 80);
			b_cos.addActionListener(this);
			add(b_cos);k++;
			b_tan=new Button("tan");
			b_tan.setBackground(Color.black);
			b_tan.setForeground(Color.white);
			b_tan.setFont(new Font("button_font", Font.PLAIN, b_tan.getHeight()+15));
			b_tan.setBounds(50+(k*90), j, 80, 80);
			b_tan.addActionListener(this);
			add(b_tan);k++;
			b_log=new Button("log");
			b_log.setBackground(Color.black);
			b_log.setForeground(Color.white);
			b_log.setFont(new Font("button_font", Font.PLAIN, b_log.getHeight()+15));
			b_log.setBounds(50+(k*90), j, 80, 80);
			b_log.addActionListener(this);
			add(b_log);k++;
			b_pi=new Button("PI");
			b_pi.setBackground(Color.black);
			b_pi.setForeground(Color.white);
			b_pi.setFont(new Font("button_font", Font.PLAIN, b_pi.getHeight()+15));
			b_pi.setBounds(50+(k*90), j, 80, 80);
			b_pi.addActionListener(this);
			add(b_pi);j+=100;k=0;
			b_com=new Button(",");
			b_com.setBackground(Color.black);
			b_com.setForeground(Color.white);
			b_com.setFont(new Font("button_font", Font.PLAIN, b_com.getHeight()+25));
			b_com.setBounds(50, j, 80, 80);
			b_com.addActionListener(this);
			add(b_com);
			b_del=new Button("Del");
			b_del.setBackground(Color.black);
			b_del.setForeground(Color.white);
			b_del.setFont(new Font("button_font", Font.PLAIN, b_del.getHeight()+15));
			b_del.setBounds(140, j, 170, 80);
			b_del.addActionListener(this);
			add(b_del);
			b_eql=new Button("=");
			b_eql.setBackground(Color.black);
			b_eql.setForeground(Color.white);
			b_eql.setFont(new Font("button_font", Font.PLAIN, b_eql.getHeight()+15));
			b_eql.setBounds(320, j, 170, 80);
			b_eql.addActionListener(this);
			add(b_eql);
		}
		else if(choice==1)
		{
			setSize(1000, 700);
			disp = new JLabel("Message");
			disp.setBounds(530, 30, 400, 60);
			disp.setForeground(new Color(28, 64, 99));
			disp.setFont(new Font("answer_font", Font.HANGING_BASELINE, disp.getHeight()-15));
			add(disp);
			
			int j=50;
			
			dec_label = new JLabel("Decimal");
			dec_label.setBounds(50, j, 350, 45);
			dec_label.setForeground(Color.darkGray);
			dec_label.setFont(new Font("answer_font", Font.BOLD, dec_label.getHeight()-10));
			add(dec_label);j+=55;
			dec=new JTextField();
			dec.setBounds(50, j, 840, 65);
			dec.setForeground(new Color(103, 174, 0));
			dec.setFont(new Font("expression_font", Font.PLAIN, dec.getHeight()-15));
			add(dec);j+=85;
			bin_label = new JLabel("Binary");
			bin_label.setBounds(50, j, 350, 45);
			bin_label.setForeground(Color.darkGray);
			bin_label.setFont(new Font("answer_font", Font.BOLD, bin_label.getHeight()-10));
			add(bin_label);j+=55;
			bin=new JTextField();
			bin.setBounds(50, j, 840, 65);
			bin.setForeground(new Color(103, 0, 252));
			bin.setFont(new Font("expression_font", Font.PLAIN, bin.getHeight()-45));
			add(bin);j+=85;
			oct_label = new JLabel("Octal");
			oct_label.setBounds(50, j, 350, 45);
			oct_label.setForeground(Color.darkGray);
			oct_label.setFont(new Font("answer_font", Font.BOLD, oct_label.getHeight()-10));
			add(oct_label);j+=55;
			oct=new JTextField();
			oct.setBounds(50, j, 840, 65);
			oct.setForeground(new Color(0, 168, 243));
			oct.setFont(new Font("expression_font", Font.PLAIN, oct.getHeight()-15));
			add(oct);j+=85;
			hex_label = new JLabel("Hexadecimal");
			hex_label.setBounds(50, j, 350, 45);
			hex_label.setForeground(Color.darkGray);
			hex_label.setFont(new Font("answer_font", Font.BOLD, hex_label.getHeight()-10));
			add(hex_label);j+=55;
			hex=new JTextField();
			hex.setBounds(50, j, 840, 65);
			hex.setForeground(new Color(105, 9, 64));
			hex.setFont(new Font("expression_font", Font.PLAIN, hex.getHeight()-15));
			add(hex);
			
			dec.addKeyListener
			(
					new KeyAdapter()
					{
						public void keyTyped(KeyEvent ke)
						{
							char ch = ke.getKeyChar();
							if((ch>='1' && ch<='9') || ch == KeyEvent.VK_BACK_SPACE)
							{
								calculateFields(ch, 0);
							}
							else
							{
								disp.setText("Invalid");
							}
						}
					}
			);
			
			bin.addKeyListener
			(
					new KeyAdapter()
					{
						public void keyTyped(KeyEvent ke)
						{
							char ch = ke.getKeyChar();
							if(ch=='0' || ch=='1' || ch == KeyEvent.VK_BACK_SPACE)
							{
								calculateFields(ch, 1);
							}
							else
							{
								disp.setText("Invalid");
							}
						}
					}
			);
			
			oct.addKeyListener
			(
					new KeyAdapter()
					{
						public void keyTyped(KeyEvent ke)
						{
							char ch = ke.getKeyChar();
							if((ch>='0' && ch<='7') || ch == KeyEvent.VK_BACK_SPACE)
							{
								calculateFields(ch, 2);
							}
							else
							{
								disp.setText("Invalid");
							}
						}
					}
			);
			
			hex.addKeyListener
			(
					new KeyAdapter()
					{
						public void keyTyped(KeyEvent ke)
						{
							char ch = ke.getKeyChar();
							if((ch>='0' && ch<='9') || (ch>='a' && ch<='f') || ch == KeyEvent.VK_BACK_SPACE)
							{
								calculateFields(ch, 3);
							}
							else
							{
								disp.setText("Invalid");
							}
						}
					}
			);
		}
		
		setVisible(true);
	}
	
	//constructor to setup the window with default calculator type
	public Calculator()
	{
		setLayout(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(1000, 700);
		setTitle("Prabin's Calculator");
		setLocation(200, 200);
		getContentPane().setBackground(new Color(225, 192, 98));
		setResizable(false);
		
		JMenuBar bar=new JMenuBar();
		JMenu lst=new JMenu("Menu");
		lst.setFont(new Font("menu_font", Font.BOLD, 25));
		lst.setForeground(new Color(28, 134, 99));
		bar.add(lst);
		JMenuItem std=new JMenuItem("Standard"),cs=new JMenuItem("Programmer"),abt=new JMenuItem("About");
		std.setFont(new Font("menu_font", Font.BOLD, 20));
		cs.setFont(new Font("menu_font", Font.BOLD, 20));
		abt.setFont(new Font("menu_font", Font.BOLD, 20));
		lst.add(std);lst.add(cs);lst.add(abt);
		setJMenuBar(bar);
		
		std.addActionListener(this);
		cs.addActionListener(this);
		abt.addActionListener(this);
		
		setFrame(0);
	}
	
	//helper function for programmer calculator
	void calculateFields(char ch,int flag)
	{
		if(flag==0)
		{
			try
			{
				if(ch!=KeyEvent.VK_BACK_SPACE)
				{
					bin.setText(Long.toBinaryString(Long.parseLong(dec.getText()+ch)));
					oct.setText(Long.toOctalString(Long.parseLong(dec.getText()+ch)));
					hex.setText(Long.toHexString(Long.parseLong(dec.getText()+ch)));
				}
				else
				{
					if(dec.getText().isEmpty())
					{
						bin.setText("");
						oct.setText("");
						hex.setText("");
					}
					else
					{
						bin.setText(Long.toBinaryString(Long.parseLong(dec.getText())));
						oct.setText(Long.toOctalString(Long.parseLong(dec.getText())));
						hex.setText(Long.toHexString(Long.parseLong(dec.getText())));
					}
				}
				disp.setText("Message");
			}
			catch(NumberFormatException ne)
			{
				if(Character.isDigit(dec.getText().charAt(dec.getText().length()-1)))
				{
					disp.setText("Out of Bound");
				}
			}
			catch(Exception e)
			{
				disp.setText("Invalid");
			}
		}
		else if(flag==1)
		{
			try
			{
				if(ch!=KeyEvent.VK_BACK_SPACE)
				{
					dec.setText(Long.toString(Long.parseLong(bin.getText()+ch,2)));
					oct.setText(Long.toOctalString(Long.parseLong(bin.getText()+ch,2)));
					hex.setText(Long.toHexString(Long.parseLong(bin.getText()+ch,2)));
				}
				else
				{
					if(bin.getText().isEmpty())
					{
						dec.setText("");
						oct.setText("");
						hex.setText("");
					}
					else
					{
						dec.setText(Long.toString(Long.parseLong(bin.getText(),2)));
						oct.setText(Long.toOctalString(Long.parseLong(bin.getText(),2)));
						hex.setText(Long.toHexString(Long.parseLong(bin.getText(),2)));
					}
				}
				disp.setText("Message");
			}
			catch(NumberFormatException ne)
			{
				if(bin.getText().charAt(bin.getText().length()-1) == '0' && bin.getText().charAt(bin.getText().length()-1) == '1')
				{
					disp.setText("Out of Bound");
				}
			}
			catch(Exception e)
			{
				disp.setText("Invalid");
			}
		}
		else if(flag==2)
		{
			try
			{
				if(ch!=KeyEvent.VK_BACK_SPACE)
				{
					bin.setText(Long.toBinaryString(Long.parseLong(oct.getText()+ch,8)));
					dec.setText(Long.toString(Long.parseLong(oct.getText()+ch,8)));
					hex.setText(Long.toHexString(Long.parseLong(oct.getText()+ch,8)));
				}
				else
				{
					if(oct.getText().isEmpty())
					{
						dec.setText("");
						bin.setText("");
						hex.setText("");
					}
					else
					{
						bin.setText(Long.toBinaryString(Long.parseLong(oct.getText(),8)));
						dec.setText(Long.toString(Long.parseLong(oct.getText(),8)));
						hex.setText(Long.toHexString(Long.parseLong(oct.getText(),8)));
					}
				}
				disp.setText("Message");
			}
			catch(NumberFormatException ne)
			{
				if(oct.getText().charAt(oct.getText().length()-1) >= '0' && oct.getText().charAt(oct.getText().length()-1) <= '7')
				{
					disp.setText("Out of Bound");
				}
			}
			catch(Exception e)
			{
				disp.setText("Invalid");
			}
		}
		else if(flag==3)
		{
			try
			{
				if(ch!=KeyEvent.VK_BACK_SPACE)
				{
					bin.setText(Long.toBinaryString(Long.parseLong(hex.getText()+ch,16)));
					dec.setText(Long.toString(Long.parseLong(hex.getText()+ch,16)));
					oct.setText(Long.toOctalString(Long.parseLong(hex.getText()+ch,16)));
				}
				else
				{
					if(hex.getText().isEmpty())
					{
						dec.setText("");
						oct.setText("");
						bin.setText("");
					}
					else
					{
						bin.setText(Long.toBinaryString(Long.parseLong(hex.getText(),16)));
						dec.setText(Long.toString(Long.parseLong(hex.getText(),16)));
						oct.setText(Long.toOctalString(Long.parseLong(hex.getText(),16)));
					}
				}
				disp.setText("Message");
			}
			catch(NumberFormatException ne)
			{
				if((hex.getText().charAt(hex.getText().length()-1) >= '0' && hex.getText().charAt(hex.getText().length()-1) <= '9')
				|| (hex.getText().charAt(hex.getText().length()-1) >= 'a' && hex.getText().charAt(hex.getText().length()-1) <= 'f'))
				{
					disp.setText("Out of Bound");
				}
			}
			catch(Exception e)
			{
				disp.setText("Invalid");
			}
		}
	}
	
	//action listener function action events
	@Override
	public void actionPerformed(ActionEvent ae)
	{
		String swch=ae.getActionCommand();
		if(swch.equals("="))
		{	try
			{
				String ans = "= "+engine.eval(expr).toString();
				disp.setFont(new Font("answer_font", Font.BOLD, disp.getHeight()-ans.length()));
				disp.setText(ans);
				ta.append("\n"+evl+" "+ans);
				expr="";
				evl="";
			}
			catch(Exception se)
			{
				disp.setText("Invalid");
			}
		}
		else if(swch.equals("pow") || swch.equals("sqrt") || swch.equals("sin") || swch.equals("cos") || swch.equals("tan") || swch.equals("log") || swch.equals("PI"))
		{
			if(swch=="PI")
			{
				expr+="Math."+swch;
				evl+=swch;
			}
			else
			{
				expr+="Math."+swch+"(";
				evl+=swch+"(";
			}
		}
		else if(swch.equals("Del"))
		{
			StringBuilder sb = new StringBuilder(expr),eb = new StringBuilder(evl);
			try
			{
				if(Character.isAlphabetic(sb.charAt(sb.length()-2)))
				{
					sb.delete(sb.lastIndexOf("M"), sb.length());
					if(eb.charAt(eb.length()-2)=='P')
						eb.delete(eb.lastIndexOf("P"), eb.length());
					else if(eb.charAt(eb.length()-4)=='p')
						eb.delete(eb.lastIndexOf("p"), eb.length());
					else if(eb.charAt(eb.length()-4)=='q' || eb.charAt(eb.length()-4)=='s')
						eb.delete(eb.lastIndexOf("s"), eb.length());
					else if(eb.charAt(eb.length()-4)=='c')
						eb.delete(eb.lastIndexOf("c"), eb.length());
					else if(eb.charAt(eb.length()-4)=='t')
						eb.delete(eb.lastIndexOf("t"), eb.length());
					else if(eb.charAt(eb.length()-4)=='l')
						eb.delete(eb.lastIndexOf("l"), eb.length());
					
				}
				else
				{
					sb.delete(sb.length()-1, sb.length());
					eb.delete(eb.length()-1, eb.length());
				}
				expr=sb.toString();
				evl=eb.toString();
			}
			catch(Exception e)
			{
				if(sb.length()==1 && eb.length()==1)
				{
					sb.delete(0,1);
					eb.delete(0,1);
					expr="";
					evl="";
				}
				disp.setText("Blank");
			}
		}
		else if(swch.equals("Programmer"))
		{
			expr="";
			evl="";
			setFrame(1);
		}
		else if(swch.equals("Standard"))
		{
			expr="";
			evl="";
			setFrame(0);
		}
		else if(swch.equals("About"))
		{
			JOptionPane.showMessageDialog(null, 
					"A Calculator for your your daily day use.\nlog() : base is e\nAngles for the trgonometric functions are in radians\n"
					+ "Developed by : Prabin Kumar Rath\nwww.explorebots.com"
					, "Application Information", JOptionPane.INFORMATION_MESSAGE);
		}
		else
		{
			evl+=swch;
			if(swch=="x")
				swch="*";
			expr+=swch;
		}
		tf.setText(evl);
	}

	//main function
	public static void main(String[] args) throws Exception
	{
		new Calculator();
	}
}