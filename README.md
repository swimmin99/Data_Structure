# Data_Structure
2022학년도 2학기 Data Structure
<scss>
  body {
  background: #000;
  padding: 2rem;
}

h2 {
  font-family: 'Arial';
  color: #fff;
  text-transform: uppercase;
  font-weight: bold;
  font-size: 3rem;
  line-height: 0.75;
}

span {
  display: block;
}

span:not(.light) {
  opacity: 0;
  animation: flashText .5s ease-out alternate infinite;
}

span.light {
  position: relative;
  display: inline-block;
  
  &:before {
    position: absolute;
    left: 0;
    top: -10%;
    width: 100%;
    height: 120%;
    background: #fff;
    filter: blur(10px);
    content: "";
    opacity: 0;
    animation: flash .5s ease-out alternate infinite;
  }
}

@keyframes flash{
  to {
    opacity: 1;
  }
}

@keyframes flashText {
  to {
    opacity: 0.15;
  }
}
  
<html>
  <table border="1">
    <th>날짜</th>
    <th>코드</th>
    <th>학습목차</th>
    <tr>
      <td>2022-10-18</td>
      <td><a href="https://github.com/swimmin99/Data_Structure/blob/main/list1.c"> List Sort 01 </a> /
      <a href="https://github.com/swimmin99/Data_Structure/blob/main/list2.c"> List Sort 02 </a></td>
      <td> 자료구조 01 - 연결리스트 </td>
    <tr>
      <td>2022-10-19</td>
      <td> <a href="https://github.com/swimmin99/Data_Structure/blob/main/Polynominal.c"> Polynominal List </a> </td>
      <td> 자료구조 02 - 연결리스트 </td>
    <tr>
      <td>2022-11-06</td>
      <td>  <a href="https://github.com/swimmin99/Data_Structure/blob/main/SparceMatrix.c"> Sparce Matrix </a> </td>
      <td> 자료구조 03 - 연결리스트  </td>
    <tr>
      <td>2022-11-06</td>
      <td> Create repository </td>
      <td> 자료구조 04 - 연결리스트  </td>
    <tr>
      <td>2022-11-09</td>
      <td> Create repository </td>
      <td> 자료구조 01 - 트리  </td>
    <tr>
      <td>2022-11-14</td>
      <td> Create repository </td>
      <td> 자료구조 02 - 트리 </td>
    <tr>
      <td>2022-11-16</td>
      <td> Create repository </td>
      <td> 자료구조 01 - 그래프 </td>
    <tr>
      <td>2022-11-16</td>
      <td> Create repository </td>
      <td> 자료구조 02 - 그래프 </td>
  </table>
  
    
  
  
</html>
