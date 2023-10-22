# 测试

本页面用于测试各类组件显示测试。

## PDF Viewer

<script src="//mozilla.github.io/pdf.js/build/pdf.mjs" type="module"></script>

<script type="module">
  // If absolute URL from the remote server is provided, configure the CORS
  // header on that server.
  var url = 'https://github.com/yhwu-is/Linear-Algebra-Left-Undone/releases/latest/download/LALU.pdf';

  // Loaded via <script> tag, create shortcut to access PDF.js exports.
  var { pdfjsLib } = globalThis;

  // The workerSrc property shall be specified.
  pdfjsLib.GlobalWorkerOptions.workerSrc = '//mozilla.github.io/pdf.js/build/pdf.worker.mjs';

  // Asynchronous download of PDF
  var loadingTask = pdfjsLib.getDocument(url);
  loadingTask.promise.then(function(pdf) {
    console.log('PDF loaded');

    // Fetch the first page
    var pageNumber = 1;
    pdf.getPage(pageNumber).then(function(page) {
      console.log('Page loaded');

      var scale = 1.5;
      var viewport = page.getViewport({scale: scale});

      // Prepare canvas using PDF page dimensions
      var canvas = document.getElementById('the-canvas');
      var context = canvas.getContext('2d');
      canvas.height = viewport.height;
      canvas.width = viewport.width;

      // Render PDF page into canvas context
      var renderContext = {
        canvasContext: context,
        viewport: viewport
      };
      var renderTask = page.render(renderContext);
      renderTask.promise.then(function () {
        console.log('Page rendered');
      });
    });
  }, function (reason) {
    // PDF loading error
    console.error(reason);
  });
</script>

<h1>PDF.js 'Hello, world!' example</h1>

<p>Please use <a href="https://mozilla.github.io/pdf.js/getting_started/#download"><i>official releases</i></a> in production environments.</p>

<canvas id="the-canvas"></canvas>

## LaTeX

simple

$$
x ={-b \pm \sqrt{b^2-4ac}\over 2a} 
$$

matrix

$$
\left\{\begin{matrix} 
  x=a + r\text{cos}\theta \\  
  y=b + r\text{sin}\theta 
\end{matrix}\right. 
$$

array

$$
\begin{array}{l} 
  a\mathop{{x}}\nolimits^{{2}}+bx+c=0 \\ 
  \Delta =\mathop{{b}}\nolimits^{{2}}-4ac \\ 
  \mathop{{x}}\nolimits_{{1,2}}=\frac{{-b \pm  
  \sqrt{{\mathop{{b}}\nolimits^{{2}}-4ac}}}}{{2a}} \\ 
  \mathop{{x}}\nolimits_{{1}}+\mathop{{x}}\nolimits_{{2}}=-\frac{{b}}{{a}} \\ 
  \mathop{{x}}\nolimits_{{1}}\mathop{{x}}\nolimits_{{2}}=\frac{{c}}{{a}} 
\end{array} 
$$

calculus

$$
\int \frac{1}{\sqrt{1-x^{2}}}\mathrm{d}x= \arcsin x +C 
$$

algebra

$$
\begin{vmatrix}  
  \mathbf{i}& \mathbf{j}& \mathbf{k} \\  
  \frac{\partial X}{\partial u}& \frac{\partial Y}{\partial u}& 0 \\  
  \frac{\partial X}{\partial v}& \frac{\partial Y}{\partial v}& 0 \\  
\end{vmatrix} 
$$

physics

$$
\mathop \Phi \nolimits_e = \oint { \mathord{ \buildrel{ \lower3pt \hbox{$ \scriptscriptstyle \rightharpoonup$}} \over E} \cdot {d \mathord{ \buildrel{ \lower3pt \hbox{$ \scriptscriptstyle \rightharpoonup$}} \over S}}  = {1 \over {{\varepsilon _0}}}\sum {q} } 
$$

Unicode

$$
%此公式需要在设置中开启unicode扩展支持 
\begin{array}{l}  
  {\huge \unicode{8751}}_\mathbb{S}  \mathbf{E} \cdot\mathrm{d}s= \cfrac{Q}{\varepsilon_0}  \\  
  {\huge \unicode{8751}}_\mathbb{S}  \mathbf{B} \cdot\mathrm{d}s= 0 \\  
  {\huge \oint}_{\mathbb{L}}^{} \mathbf{E} \cdot \mathrm{d}l=-\cfrac{\mathrm{d}\Phi _{\mathbf{B}}}{\mathrm{d}t }  \\  
  {\huge \oint}_{\mathbb{L}}^{} \mathbf{B} \cdot \mathrm{d}l=\mu_0I+ \mu_0 \varepsilon_0\cfrac{\mathrm{d}\Phi _{\mathbf{E}}}{\mathrm{d}t }   
\end{array} 
$$

mhchem

$$
%此公式需要在【设置】中开启mhchem扩展支持 具体用法请参考【帮助】2.11.2 
\ce{SO4^2- + Ba^2+ -> BaSO4 v} 
$$