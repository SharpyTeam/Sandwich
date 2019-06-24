import {p} from './module';
import _ from 'lodash';

p(12);
console.log(_.defaults({ 'a': 1 }, { 'a': 3, 'b': 2 }));