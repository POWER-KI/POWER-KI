<h3>WRAP</h3>
WRAP (WRP in POWER-KI) are external Win DLL that make possible to extend PWK with user code.</br>
We provide a WIN template Project that you can use to easily create your WRAP DLL.</br>
To install copy the zip file in the project Templates directory of your Visual Studio like:</br></br>

<code>C:\Users\XXXX\Documents\Visual Studio 2015\Templates\ProjectTemplates</code></br>

From PWK the use is very simple:</br>

<code>
wrp=WRP_OPN("YourWrpDll");<br>
res=WRP_EXC(Wrp,"YourFunctionName", par1, par2);
</code>
